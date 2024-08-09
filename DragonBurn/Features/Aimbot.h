#pragma once
#define _USE_MATH_DEFINES
#define MAXV 10000e9
#include <math.h>
#include <thread>
#include <chrono>
#include "..\Game\Game.h"
#include "..\Game\Entity.h"
#include "..\Config\MenuConfig.hpp"
#include <iostream>
#include "..\Game\View.hpp"
#include "..\Features/RCS.h"
#include "TriggerBot.h"

extern "C" {
#include "..\Helpers\Mouse.h"
#include "..\Game\Entity.h"
}


namespace AimControl
{
    inline int HotKey = VK_LMENU;
    inline int AimBullet = 1;
    inline bool ScopeOnly = false;
    inline bool AutoShot = false;
    inline bool IgnoreFlash = false;
    inline float AimFov = 5;
    inline float AimFovMin = 0.f;
    inline float Smooth = 2.0f;
    inline std::vector<int> HitboxList{ BONEINDEX::head };
    inline std::vector<int> HotKeyList{ VK_LMENU, VK_LBUTTON, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL };
    inline bool HasTarget = false;


    void AimControl::AimBot(const CEntity& Local, Vec3 LocalPos, std::vector<Vec3>& AimPosList);
    void AimControl::switchToggle();
    void AimControl::SetHotKey(int Index);
}
