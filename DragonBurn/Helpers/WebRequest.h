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
#include <regex>
#include <array>

namespace Web
{
	/// <summary>
	/// Checks is internet connection is available
	/// </summary>
	/// <returns>0/1</returns>
	bool CheckConnection();

	/// <summary>
	/// Gets data by url using curl
	/// </summary>
	/// <param name="url"></param>
	/// <param name="buffer to write"></param>
	/// <returns>0/1</returns>
	bool Get(const std::string&, std::string&);

	/// <summary>
	/// Posts data by url using curl
	/// </summary>
	/// <param name="url"></param>
	/// <param name="data"></param>
	/// <param name="buffer to write"></param>
	/// <returns>0/1</returns>
	bool Post(const std::string&, std::string&, std::string&);
}