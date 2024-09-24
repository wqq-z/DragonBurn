//
//______                            ______                  
//|  _  \                           | ___ \                 
//| | | |_ __ __ _  __ _  ___  _ __ | |_/ /_   _ _ __ _ __  
//| | | | '__/ _` |/ _` |/ _ \| '_ \| ___ \ | | | '__| '_ \ 
//| |/ /| | | (_| | (_| | (_) | | | | |_/ / |_| | |  | | | |
//|___/ |_|  \__,_|\__, |\___/|_| |_\____/ \__,_|_|  |_| |_|
//                  __/ |                                   
//                 |___/                                    
//https://github.com/ByteCorum/DragonBurn

#include "WebRequest.h"

bool Web::CheckConnection() 
{
    int result = system("ping google.com > nul");
    if (result == 0)
        return true;
    else
        return false;
}

bool Web::Get(const std::string& url, std::string& response) 
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

bool Web::Post(const std::string& url, std::string& params) 
{
    return true;
}