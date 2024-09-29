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
#include <json.hpp>
#include <imgui.h>

namespace ValuesHandler
{
	/// <summary>
	/// Reads any value from json cfg
	/// </summary>
	/// <typeparam name="ValueType"></typeparam>
	/// <param name="node"></param>
	/// <param name="key"></param>
	/// <param name="defaultValue"></param>
	/// <param name="buff"></param>
	template <typename ValueType>
	void ReadValue(const nlohmann::json&, const std::string&, const ValueType&, ValueType&);

	/// <summary>
	/// Reads vector from json cfg
	/// </summary>
	/// <param name="node"></param>
	/// <param name="key"></param>
	/// <param name="defaultValue"></param>
	/// <param name="buff"></param>
	void ReadVector(const nlohmann::json&, const std::string&, const std::vector<int>&, std::vector<int>&);

	/// <summary>
	/// Reads color from json cfg
	/// </summary>
	/// <param name="node"></param>
	/// <param name="key"></param>
	/// <param name="defaultValue"></param>
	/// <param name="buff"></param>
	void ReadColor(const nlohmann::json&, const std::string&, const ImColor&, ImColor&);

	/// <summary>
	/// Reads pos from json cfg
	/// </summary>
	/// <param name="node"></param>
	/// <param name="key"></param>
	/// <param name="defaultValue"></param>
	/// <param name="buff"></param>
	void ReadPos(const nlohmann::json&, const std::string&, const ImVec2&, ImVec2&);

	/// <summary>
	/// Saves color to json cfg
	/// </summary>
	/// <param name="node"></param>
	/// <param name="key"></param>
	/// <param name="color"></param>
	void SaveColor(nlohmann::json&, const std::string&, const ImColor&);

	/// <summary>
	/// Saves pos to json cfg
	/// </summary>
	/// <param name="node"></param>
	/// <param name="key"></param>
	/// <param name="pos"></param>
	void SavePos(nlohmann::json&, const std::string&, const ImVec2&);
	
}