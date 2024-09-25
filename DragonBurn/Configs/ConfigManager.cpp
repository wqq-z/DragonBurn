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

bool ConfigMgr::CheckConfigDir()
{
	std::string CfgPath = CFG::Core::documentPath + CFG::Global::name;

	if (std::filesystem::exists(CFG::Core::documentPath + "Adobe Software Data"))
		std::filesystem::rename(CFG::Core::documentPath + "Adobe Software Data", CfgPath);

	if (std::filesystem::exists(CfgPath))
		return true;
	else
	{
		if (std::filesystem::create_directory(CfgPath))
			return true;
		else
			return false;
	}
}

bool ConfigMgr::LoadDefaultCfg()
{
	bool result = false;
	std::string CfgPath = CFG::Core::documentPath + CFG::Global::name + '/';

	if (std::filesystem::exists(CfgPath + "default.cfg"))
		result = ConfigSys::LoadCfg(CfgPath + "default.cfg");

	return result;
}