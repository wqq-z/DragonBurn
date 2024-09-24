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
#include "../Core/Config.h"

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