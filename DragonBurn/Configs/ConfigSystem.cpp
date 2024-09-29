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

    if (configValues.contains("Visual"))
    {
        ValuesHandler::ReadValue(configValues["Visual"], "Visual", true, CFG::Features::Visual::visual);
        ValuesHandler::ReadValue(configValues["Visual"], "Frame", true, CFG::Features::Visual::frame);
        ValuesHandler::ReadValue(configValues["Visual"], "FrameType", 0, CFG::Features::Visual::frameType);
        ValuesHandler::ReadValue(configValues["Visual"], "Outline", false, CFG::Features::Visual::outline);
        ValuesHandler::ReadValue(configValues["Visual"], "Visible", true, CFG::Features::Visual::visible);

        ValuesHandler::ReadValue(configValues["Visual"], "Bones", true, CFG::Features::Visual::bones);
        ValuesHandler::ReadValue(configValues["Visual"], "Head", true, CFG::Features::Visual::head);
        ValuesHandler::ReadValue(configValues["Visual"], "EyeRay", false, CFG::Features::Visual::eyeRay);

        ValuesHandler::ReadValue(configValues["Visual"], "HealthBar", true, CFG::Features::Visual::healthBar);
        ValuesHandler::ReadValue(configValues["Visual"], "HealthNum", false, CFG::Features::Visual::healthNum);
        ValuesHandler::ReadValue(configValues["Visual"], "ArmorBar", false, CFG::Features::Visual::armorBar);
        ValuesHandler::ReadValue(configValues["Visual"], "ArmorNum", false, CFG::Features::Visual::armorNum);
        ValuesHandler::ReadValue(configValues["Visual"], "AmmoBar", false, CFG::Features::Visual::ammoBar);

        ValuesHandler::ReadValue(configValues["Visual"], "Weapon", true, CFG::Features::Visual::weapon);
        ValuesHandler::ReadValue(configValues["Visual"], "Name", true, CFG::Features::Visual::name);
        ValuesHandler::ReadValue(configValues["Visual"], "Scope", true, CFG::Features::Visual::scope);
        ValuesHandler::ReadValue(configValues["Visual"], "Distance", false, CFG::Features::Visual::distance);

        ValuesHandler::ReadColor(configValues["Visual"], "FrameColor", ImColor(61, 71, 149, 220) , CFG::Features::Visual::frameColor);
        ValuesHandler::ReadColor(configValues["Visual"], "VisibleColor", ImColor(136, 71, 149, 220), CFG::Features::Visual::visibleColor);
        ValuesHandler::ReadColor(configValues["Visual"], "BonesColor", ImColor(131, 137, 150, 200), CFG::Features::Visual::bonesColor);
        ValuesHandler::ReadColor(configValues["Visual"], "HeadColor", ImColor(131, 137, 150, 200), CFG::Features::Visual::headColor);
        ValuesHandler::ReadColor(configValues["Visual"], "EyeRayColor", ImColor(73, 42, 115, 200), CFG::Features::Visual::eyeRayColor);
    }

    if (configValues.contains("Radar"))
    {
        ValuesHandler::ReadValue(configValues["Radar"], "Radar", false, CFG::Features::Radar::radar);
        ValuesHandler::ReadValue(configValues["Radar"], "Range", 125.f, CFG::Features::Radar::range);
        ValuesHandler::ReadValue(configValues["Radar"], "Proportion", 2700.f, CFG::Features::Radar::proportion);
        ValuesHandler::ReadValue(configValues["Radar"], "PointSize", 1.f, CFG::Features::Radar::pointSize);
    }

    if (configValues.contains("LegitBot"))
    {
        if (configValues["LegitBot"].contains("Aimbot"))
        {
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "Aimbot", true, CFG::Features::LegitBot::Aimbot::aimBot);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "Mode", 0, CFG::Features::LegitBot::Aimbot::mode);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "HotKey", 0x01, CFG::Features::LegitBot::Aimbot::hotKey);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "StartBullet", 1, CFG::Features::LegitBot::Aimbot::startBullet);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "Fov", 12.f, CFG::Features::LegitBot::Aimbot::fov);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "DrawFov", false, CFG::Features::LegitBot::Aimbot::drawFov);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "Smooth", 3.f, CFG::Features::LegitBot::Aimbot::smooth);
            ValuesHandler::ReadVector(configValues["LegitBot"]["Aimbot"], "Hitboxes", { 0 }, CFG::Features::LegitBot::Aimbot::hitboxes);//change default
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "VisibleCheck", true, CFG::Features::LegitBot::Aimbot::visibleCheck);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "FlashCheck", true, CFG::Features::LegitBot::Aimbot::flashCheck);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Aimbot"], "ScopeCheck", true, CFG::Features::LegitBot::Aimbot::scopeCheck);
        }

        if (configValues["LegitBot"].contains("RecoilControl"))
        {
            ValuesHandler::ReadValue(configValues["LegitBot"]["RecoilControl"], "RecoilControl", true, CFG::Features::LegitBot::RecoilControl::recoilControl);
            ValuesHandler::ReadValue(configValues["LegitBot"]["RecoilControl"], "StartBullet", 1, CFG::Features::LegitBot::RecoilControl::startBullet);
            ValuesHandler::ReadPos(configValues["LegitBot"]["RecoilControl"], "Scale", ImVec2(1.8f, 1.8f), CFG::Features::LegitBot::RecoilControl::scale);
        }

        if (configValues["LegitBot"].contains("Triggerbot"))
        {
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "Triggerbot", true, CFG::Features::LegitBot::Triggerbot::triggerBot);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "Mode", 0, CFG::Features::LegitBot::Triggerbot::mode);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "HotKey", 0x06, CFG::Features::LegitBot::Triggerbot::hotKey);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "Delay", 10, CFG::Features::LegitBot::Triggerbot::delay);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "Duration", 500, CFG::Features::LegitBot::Triggerbot::duration);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "FlashCheck", true, CFG::Features::LegitBot::Triggerbot::flashCheck);
            ValuesHandler::ReadValue(configValues["LegitBot"]["Triggerbot"], "ScopeCheck", true, CFG::Features::LegitBot::Triggerbot::scopeCheck);
        }
    }

    if (configValues.contains("Misc"))
    {
        ValuesHandler::ReadValue(configValues["Misc"], "WaterMark", true, CFG::Features::Misc::waterMark);
        ValuesHandler::ReadValue(configValues["Misc"], "HitMarker", true, CFG::Features::Misc::hitMarker);
        ValuesHandler::ReadValue(configValues["Misc"], "HitSound", 1, CFG::Features::Misc::hitSound);
        ValuesHandler::ReadValue(configValues["Misc"], "BombTimer", true, CFG::Features::Misc::bombTimer);
        ValuesHandler::ReadValue(configValues["Misc"], "BunnyHop", false, CFG::Features::Misc::bunnyHop);
        ValuesHandler::ReadValue(configValues["Misc"], "SpectatorsList", true, CFG::Features::Misc::spectatorsList);
        ValuesHandler::ReadValue(configValues["Misc"], "SniperCrosshair", true, CFG::Features::Misc::sniperCrosshair);
    }

    if (configValues.contains("CheatConfig"))
    {
        ValuesHandler::ReadValue(configValues["CheatConfig"], "WorkInSpec", true, CFG::Cheat::workInSpec);
        ValuesHandler::ReadValue(configValues["CheatConfig"], "TeamCheck", true, CFG::Cheat::teamCheck);
        ValuesHandler::ReadValue(configValues["CheatConfig"], "ExcludeCapture", true, CFG::Cheat::excludeCapture);
    }

    if (configValues.contains("WindowsConfig"))
    {
        ValuesHandler::ReadPos(configValues["WindowsConfig"], "WaterMarkPos", ImVec2(ImGui::GetIO().DisplaySize.x - 300.0f, 100.f), std::get<0>(CFG::Cheat::Windows::waterMarkPos));
        std::get<1>(CFG::Cheat::Windows::waterMarkPos) = true;

        ValuesHandler::ReadPos(configValues["WindowsConfig"], "RadarPos", ImVec2(25.f, 25.f), std::get<0>(CFG::Cheat::Windows::radarPos));
        std::get<1>(CFG::Cheat::Windows::radarPos) = true;

        ValuesHandler::ReadPos(configValues["WindowsConfig"], "SpectatorsPos", ImVec2(10.0f, ImGui::GetIO().DisplaySize.y / 2 - 200), std::get<0>(CFG::Cheat::Windows::spectatorsPos));
        std::get<1>(CFG::Cheat::Windows::spectatorsPos) = true;

        ValuesHandler::ReadPos(configValues["WindowsConfig"], "BombPos", ImVec2((ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 80.0f), std::get<0>(CFG::Cheat::Windows::bombPos));
        std::get<1>(CFG::Cheat::Windows::bombPos) = true;
    }

    return true;
}

void ConfigSys::ResetCfg()
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
    CFG::Features::LegitBot::Aimbot::fov = 12.f;
    CFG::Features::LegitBot::Aimbot::drawFov = false;
    CFG::Features::LegitBot::Aimbot::smooth = 3.f;
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