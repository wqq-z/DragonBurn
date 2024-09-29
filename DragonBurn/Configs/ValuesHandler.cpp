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

#include "ValuesHandler.h"

template <typename ValueType>
void ValuesHandler::ReadValue(const nlohmann::json& node, const std::string& key, const ValueType& defaultValue, ValueType& buff)
{
    if (node.contains(key) && !node[key].is_null()) 
    {
        buff = node[key].get<ValueType>();
    }
    else
        buff = defaultValue;
}

void ValuesHandler::ReadVector(const nlohmann::json& node, const std::string& key, const std::vector<int>& defaultValue, std::vector<int>& buff)
{
    if (node.contains(key) && !node[key].is_null() && node[key].is_array())
    {
        std::vector<int> result;
        for (const auto& element : node[key])
        {
            result.push_back(element.get<int>());
        }
        buff = result;
    }
    else
        buff = defaultValue;
}

void ValuesHandler::ReadColor(const nlohmann::json& node, const std::string& key, const ImColor& defaultValue, ImColor& buff)
{
    if (node.contains(key) && !node[key].is_null())
    {
        buff.Value.x = node[key]["r"].get<int>();
        buff.Value.y = node[key]["g"].get<int>();
        buff.Value.z = node[key]["b"].get<int>();
        buff.Value.w = node[key]["a"].get<int>();
    }
    else
        buff = defaultValue;
}

void ValuesHandler::ReadPos(const nlohmann::json& node, const std::string& key, const ImVec2& defaultValue, ImVec2& buff)
{
    if (node.contains(key) && !node[key].is_null())
    {
        buff.x = node[key]["x"].get<float>();
        buff.y = node[key]["y"].get<float>();
    }
    else
        buff = defaultValue;
}

void ValuesHandler::SaveColor(nlohmann::json& node, const std::string& key, const ImColor& color)
{
    node[key]["r"] = color.Value.x;
    node[key]["g"] = color.Value.y;
    node[key]["b"] = color.Value.z;
    node[key]["a"] = color.Value.w;
}

void ValuesHandler::SavePos(nlohmann::json& node, const std::string& key, const ImVec2& pos)
{
    node[key]["x"] = pos.x;
    node[key]["y"] = pos.y;
}
