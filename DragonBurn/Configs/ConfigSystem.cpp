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

#include "ConfigManager.h"


bool ConfigSys::LoadCfg(const std::string& path)
{
	if (!std::filesystem::exists(path))
		return false;

	nlohmann::json configValues;
    std::ifstream configFile(path);
    if (configFile)
        configFile >> configValues;
    else
        return false;

    //finish LoadCfg

    if (configValues.contains("Visual"))
    {

    }

    if (configValues.contains("ExternalRadar"))
    {

    }

    if (configValues.contains("LegitBot"))
    {
        if (configValues["LegitBot"].contains("Aimbot"))
        {

        }

        if (configValues["LegitBot"].contains("RecoilControl"))
        {

        }

        if (configValues["LegitBot"].contains("Triggerbot"))
        {

        }
    }

    if (configValues.contains("Misc"))
    {

    }

    if (configValues.contains("CheatConfig"))
    {

    }

    if (configValues.contains("WindowsConfig"))
    {

    }
}