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

void ResetCfg() 
{
    //Visual
    CFG::Features::Visual::visual = true;
    CFG::Features::Visual::frame = true;
    CFG::Features::Visual::frameType = 0;
    CFG::Features::Visual::outline = false;
    CFG::Features::Visual::visible = true;

    CFG::Features::Visual::bones = true;
    CFG::Features::Visual::head = true;
    CFG::Features::Visual::eyeRay = false;

    CFG::Features::Visual::healthBar = true;
    CFG::Features::Visual::healthNum = false;
    CFG::Features::Visual::armorBar = false;
    CFG::Features::Visual::armorNum = false;
    CFG::Features::Visual::ammoBar = false;

    CFG::Features::Visual::weapon = true;
    CFG::Features::Visual::name = true;
    CFG::Features::Visual::scope = true;
    CFG::Features::Visual::distance = false;

    CFG::Features::Visual::frameColor = ImColor(61, 71, 149, 220);
    CFG::Features::Visual::visibleColor = ImColor(136, 71, 149, 220);
    CFG::Features::Visual::bonesColor = ImColor(131, 137, 150, 200);
    CFG::Features::Visual::headColor = ImColor(131, 137, 150, 200);
    CFG::Features::Visual::eyeRayColor = ImColor(73, 42, 115, 200);

    //Radar
    CFG::Features::Radar::radar = false;
    CFG::Features::Radar::range = 125.f;
    CFG::Features::Radar::proportion = 2700.f;
    CFG::Features::Radar::pointSize = 1.f;

    //LegitBot
    //Aimbot
    CFG::Features::LegitBot::Aimbot::aimBot = true;
    CFG::Features::LegitBot::Aimbot::mode = 0;
    CFG::Features::LegitBot::Aimbot::hotKey = 0x01;
    CFG::Features::LegitBot::Aimbot::startBullet = 1;
    CFG::Features::LegitBot::Aimbot::fov = 12;
    CFG::Features::LegitBot::Aimbot::drawFov = false;
    CFG::Features::LegitBot::Aimbot::smooth = 3;
    CFG::Features::LegitBot::Aimbot::hitboxes = {0};//init
    CFG::Features::LegitBot::Aimbot::visibleCheck = true;
    CFG::Features::LegitBot::Aimbot::flashCheck = true;
    CFG::Features::LegitBot::Aimbot::scopeCheck = true;

    //RecoilControl
    CFG::Features::LegitBot::RecoilControl::recoilControl = true;
    CFG::Features::LegitBot::RecoilControl::startBullet = 1;
    CFG::Features::LegitBot::RecoilControl::scale = ImVec2(1.8f, 1.8f);

    //Triggerbot
    CFG::Features::LegitBot::Triggerbot::triggerBot = true;
    CFG::Features::LegitBot::Triggerbot::mode = 0;
    CFG::Features::LegitBot::Triggerbot::hotKey = 0x06;
    CFG::Features::LegitBot::Triggerbot::delay = 10;
    CFG::Features::LegitBot::Triggerbot::duration = 500;
    CFG::Features::LegitBot::Triggerbot::flashCheck = true;
    CFG::Features::LegitBot::Triggerbot::scopeCheck = true;

    //Misc
    CFG::Features::Misc::waterMark = true;
    CFG::Features::Misc::hitMarker = true;
    CFG::Features::Misc::hitSound = 1;
    CFG::Features::Misc::bombTimer = true;
    CFG::Features::Misc::bunnyHop = false;
    CFG::Features::Misc::spectatorsList = true;
    CFG::Features::Misc::sniperCrosshair = true;

    //Cheat
    //Main
    CFG::Cheat::workInSpec = true;
    CFG::Cheat::teamCheck = true;
    CFG::Cheat::excludeCapture = true;

    //Windows
    CFG::Cheat::Windows::waterMarkPos = std::tuple<ImVec2, bool>(ImVec2(ImGui::GetIO().DisplaySize.x - 300.0f, 100.f), true);
    CFG::Cheat::Windows::radarPos = std::tuple<ImVec2, bool>(ImVec2(25.f, 25.f), true);
    CFG::Cheat::Windows::spectatorsPos = std::tuple<ImVec2, bool>(ImVec2(10.0f, ImGui::GetIO().DisplaySize.y / 2 - 200), true);
    CFG::Cheat::Windows::bombPos = std::tuple<ImVec2, bool>(ImVec2((ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 80.0f), true);
}