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

#include "Setup.h"

int Setup::CheckProgVersion()
{
    const std::string curVersionUrl = "https://raw.githubusercontent.com/ByteCorum/DragonBurn/data/version";
    std::string curVersion;

    if (!Web::CheckConnection())
        return 0;

    if (!Web::Get(curVersionUrl, curVersion))
        return 1;

    if (curVersion != CFG::Global::version)
    {
        return 2;
    }

    return 3;
}

bool Setup::GetCfgPath()
{
    wchar_t* userProfile = nullptr;
    size_t len = 0;
    _wdupenv_s(&userProfile, &len, L"USERPROFILE");

    if (userProfile) 
    {
        std::filesystem::path documentsPath = std::filesystem::path(userProfile) / "Documents/";
        CFG::Core::documentPath = documentsPath.string();
        free(userProfile);

        return true;
    }
    else
        return false;
}