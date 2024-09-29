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
#include <string>
#include <filesystem>
#include "../Core/Config.h"
#include "../Helpers/WebRequest.h"

namespace Setup
{
	/// <summary>
	/// Checks if program version is newest
	/// </summary>
	/// <returns>status</returns>
	int CheckProgVersion();

	/// <summary>
	/// Gets path to documents dir
	/// </summary>
	/// <returns>0/1</returns>
	bool GetCfgPath();

	/// <summary>
	/// Starts all gui
	/// </summary>
	/// <returns></returns>
	bool StartCheatOverlay();
}