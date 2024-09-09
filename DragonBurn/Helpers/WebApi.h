#pragma once
//#include <curl/curl.h>
#include <string>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <regex>

namespace Web
{
    //size_t writeCallback(void* ptr, size_t size, size_t nmemb, std::string* buffer) {
    //    buffer->append((char*)ptr, size * nmemb);
    //    return size * nmemb;
    //}

    //bool LoadData(std::string url, std::string& response)
    //{
    //    CURL* curl;
    //    CURLcode res;

    //    curl = curl_easy_init();
    //    if (curl)
    //    {
    //        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    //        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
    //            writeCallback);
    //        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    //        res = curl_easy_perform(curl);

    //        if (res != CURLE_OK)
    //        {
    //            return false;
    //        }

    //        curl_easy_cleanup(curl);
    //        return true;
    //    }
    //    else
    //    {
    //        return false;
    //    }
    //}

    inline bool CheckConnection()
    {
        int result = system("ping google.com > nul");
        if (result == 0)
            return true;
        else
            return false;
    }

    inline bool Get(std::string url, std::string& response)
    {
        response = "";
        std::string cmd = "curl -s -X GET " + url;

        std::array<char, 128> buffer;
        std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);

        if (!pipe)
        {
            return false;
        }
        while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr)
        {
            response += buffer.data();
        }

        std::regex pattern("\\d{3}:");
        if (std::regex_search(response, pattern))
        {
            return false;
        }

        return true;
    }

    inline bool Post(std::string url, std::string& params)
    {
        return true;
    }
}