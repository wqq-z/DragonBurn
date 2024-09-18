#pragma once
#include <chrono>

#include "../Game/Game.h"
#include "../Game/Entity.h"
#include "../Core/Config.h"

namespace TriggerBot
{
	inline int TriggerDelay = 10; // ms
	inline int ShotDuration = 400; // ms
	inline bool ScopeOnly = true;
	inline bool IgnoreFlash = false;
	inline int HotKey = VK_CAPITAL;
	inline std::vector<int> HotKeyList{VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL};
	inline std::chrono::time_point<std::chrono::system_clock> timepoint = std::chrono::system_clock::now();
	inline std::chrono::time_point<std::chrono::system_clock> startTime = std::chrono::system_clock::now();
	inline bool recorded = false;
	inline bool VisibleCheck = true;

	inline void SetHotKey(int Index)
	{
		HotKey = HotKeyList.at(Index);
	}

	// Triggerbot
	void Run(const CEntity& LocalEntity);
	//void TargetCheck(const CEntity& LocalEntity) noexcept;
	bool CheckScopeWeapon(const CEntity& LocalEntity);
	bool CheckWeapon(const CEntity& LocalEntity);
}