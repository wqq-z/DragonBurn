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

#pragma once
#include <filesystem>
#include <json.hpp>
#include <fstream>
#include "../Core/Config.h"

namespace ConfigMgr
{
	/// <summary>
	/// Checks is cfg dir exist(creates); Renames hiden cfg dir
	/// </summary>
	/// <returns>0/1</returns>
	bool CheckConfigDir();

	/// <summary>
	/// Loads default cfg values
	/// </summary>
	/// <returns>0/1</returns>
	bool LoadDefaultCfg();
}

namespace ConfigSys
{
	/// <summary>
	/// Loads config values from cfg by path
	/// </summary>
	/// <param name="path"></param>
	/// <returns>0/1</returns>
	bool LoadCfg(const std::string&);

	/// <summary>
	/// Saves config values to cfg by path
	/// </summary>
	/// <param name="path"></param>
	/// <returns>0/1</returns>
	bool SaveCfg(const std::string&);


	/// <summary>
	/// Resets current config to default
	/// </summary>
	void ResetCfg();

	/// <summary>
	/// Deletes config file by path
	/// </summary>
	/// <param name="path"></param>
	/// <returns>0/1</returns>
	bool DelCfg(const std::string&);
}