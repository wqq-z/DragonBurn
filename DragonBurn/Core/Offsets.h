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
#include <Windows.h>
#include <json.hpp>
#include "../Helpers/WebRequest.h"

using json = nlohmann::json;

class Offsets
{
public:
	Offsets();
	~Offsets();
	int UpdateOffsets();

	DWORD EntityList;
	DWORD Matrix;
	DWORD ViewAngle;
	DWORD LocalPlayerController;
	DWORD LocalPlayerPawn;
	DWORD GlobalVars;
	DWORD PlantedC4;
	DWORD InputSystem;
	DWORD Sensitivity;

	struct
	{
		DWORD Jump;
		DWORD Left;
		DWORD Right;
		DWORD Attack;
	}Buttons;

	struct
	{
		DWORD IsAlive;
		DWORD PlayerPawn;
		DWORD iszPlayerName;
	}Entity;

	struct
	{
		DWORD BulletServices;
		DWORD CameraServices;
		DWORD pClippingWeapon;

		DWORD isScoped;
		DWORD isDefusing;
		DWORD TotalHit;
		DWORD Pos;
		DWORD CurrentArmor;
		DWORD MaxHealth;
		DWORD CurrentHealth;
		DWORD GameSceneNode;
		DWORD BoneArray;
		DWORD angEyeAngles;
		DWORD vecLastClipCameraPos;
		DWORD iShotsFired;
		DWORD flFlashDuration;
		DWORD aimPunchAngle;
		DWORD aimPunchCache;
		DWORD iIDEntIndex;
		DWORD iTeamNum;
		DWORD iFovStart;
		DWORD fFlags;
		DWORD bSpottedByMask;
		DWORD AbsVelocity;
		DWORD m_bWaitForNoAttack;

	} Pawn;

	struct
	{
		DWORD RealTime;
		DWORD FrameCount;
		DWORD MaxClients;
		DWORD IntervalPerTick;
		DWORD CurrentTime;
		DWORD CurrentTime2;
		DWORD TickCount;
		DWORD IntervalPerTick2;
		DWORD CurrentNetchan;
		DWORD CurrentMap;
		DWORD CurrentMapName;
	} GlobalVar;

	struct
	{
		DWORD steamID;
		DWORD hPawn;
		DWORD pObserverServices;
		DWORD hObserverTarget;
		DWORD hController;
		DWORD PawnArmor;
		DWORD HasDefuser;
		DWORD HasHelmet;
	} PlayerController;

	struct
	{
		DWORD AttributeManager;
	} EconEntity;

	struct
	{
		DWORD WeaponDataPTR;
		DWORD szName;
		DWORD Clip1;
		DWORD MaxClip;
		DWORD Item;
		DWORD ItemDefinitionIndex;
	} WeaponBaseData;

	struct
	{
		DWORD bBeingDefused;
		DWORD flDefuseCountDown;
		DWORD nBombSite;
	} C4;

private:
	void SetOffsets(const std::string&, const std::string&, const std::string&);
};

inline Offsets Offset;