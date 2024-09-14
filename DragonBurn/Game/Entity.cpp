#include "Entity.h"
#include "../Helpers/Logger.h"


std::map<int, std::string> CEntity::weaponNames = {
	{1, "deagle"},
	{2, "elite"},
	{3, "fiveseven"},
	{4, "glock"},
	{7, "ak47"},
	{8, "aug"},
	{9, "awp"},
	{10, "famas"},
	{11, "g3Sg1"},
	{13, "galilar"},
	{14, "m249"},
	{17, "mac10"},
	{19, "p90"},
	{23, "mp5sd"},
	{24, "ump45"},
	{25, "xm1014"},
	{26, "bizon"},
	{27, "mag7"},
	{28, "negev"},
	{29, "sawedoff"},
	{30, "tec9"},
	{31, "zeus"},
	{32, "p2000"},
	{33, "mp7"},
	{34, "mp9"},
	{35, "nova"},
	{36, "p250"},
	{38, "scar20"},
	{39, "sg556"},
	{40, "ssg08"},
	{42, "ct_knife"},
	{43, "flashbang"},
	{44, "hegrenade"},
	{45, "smokegrenade"},
	{46, "molotov"},
	{47, "decoy"},
	{48, "incgrenade"},
	{49, "c4"},
	{16, "m4a1"},
	{61, "usp"},
	{60, "m4a1_silencer"},
	{63, "cz75a"},
	{64, "revolver"},
	{59, "t_knife"}
};

inline std::string CEntity::GetWeaponName(int weaponID) {
	auto it = weaponNames.find(weaponID);
	if (it != weaponNames.end()) {
		return it->second;
	}
	return "Weapon_None";
}

bool CEntity::UpdateController(const DWORD64& PlayerControllerAddress)
{
	if (PlayerControllerAddress == 0)
		return false;
	this->Controller.Address = PlayerControllerAddress;

	if (!this->Controller.GetHealth())
		return false;
	if (!this->Controller.GetIsAlive())
		return false;
	if (!this->Controller.GetTeamID())
		return false;
	if (!this->Controller.GetPlayerName())
		return false;
	if (!this->Controller.GetPlayerSteamID())
		return false;

	this->Pawn.Address = this->Controller.GetPlayerPawnAddress();

	return true;
}

bool CEntity::UpdatePawn(const DWORD64& PlayerPawnAddress)
{
	if (PlayerPawnAddress == 0)
		return false;
	this->Pawn.Address = PlayerPawnAddress;

	if (!this->Pawn.GetCameraPos())
		return false;
	if (!this->Pawn.GetPos())
		return false;
	if (!this->Pawn.GetViewAngle())
		return false;
	if (!this->Pawn.GetWeaponName())
		return false;
	if (!this->Pawn.GetAimPunchAngle())
		return false;
	if (!this->Pawn.GetShotsFired())
		return false;
	if (!this->Pawn.GetHealth())
		return false;
	if (!this->Pawn.GetAmmo())
		return false;
	if (!this->Pawn.GetMaxAmmo())
		return false;
	if (!this->Pawn.GetArmor())
		return false;
	if (!this->Pawn.GetTeamID())
		return false;
	if (!this->Pawn.GetFov())
		return false;
	if (!this->Pawn.GetSpotted())
		return false;
	if (!this->Pawn.GetFFlags())
		return false;
	if (!this->Pawn.GetDefusing())
		return false;
	if (!this->Pawn.GetFlashDuration())
		return false;
	if (!this->Pawn.GetVelocity())
		return false;
	if (!this->Pawn.GetAimPunchCache())
		return false;
	if (!this->Pawn.BoneData.UpdateAllBoneData(PlayerPawnAddress))
		return false;

	return true;
}

bool CEntity::UpdateClientData()
{
	if (!this->Client.GetSensitivity())
		return false;

	return true;
}

bool PlayerController::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Pawn.iTeamNum, this->TeamID);
}

bool PlayerController::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Pawn.CurrentHealth, this->Health);
}

bool PlayerController::GetIsAlive()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Entity.IsAlive, this->AliveStatus);
}

bool PlayerController::GetPlayerName()
{
	char Buffer[MAX_PATH]{};

	Log::Debug("Entity.cpp 157		" + std::to_string(Address + Offset.Entity.iszPlayerName), true);
	if (!memoryManager.ReadMemory(Address + Offset.Entity.iszPlayerName, Buffer, MAX_PATH))
		return false;

	//if (!this->SteamID)
	//	this->PlayerName = "BOT " + std::string(Buffer);
	//else
	this->PlayerName = Buffer;

	if (this->PlayerName.empty())
		this->PlayerName = "Name_None";

	return true;
}

bool PlayerController::GetPlayerSteamID()
{
	return GetDataAddressWithOffset<INT64>(Address, Offset.PlayerController.m_steamID, this->SteamID);
}

bool PlayerPawn::GetViewAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset.Pawn.angEyeAngles, this->ViewAngle);
}

bool PlayerPawn::GetCameraPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset.Pawn.vecLastClipCameraPos, this->CameraPos);
}

bool PlayerPawn::GetSpotted()
{
	return GetDataAddressWithOffset<DWORD64>(Address, Offset.Pawn.bSpottedByMask, this->bSpottedByMask);
}


bool PlayerPawn::GetWeaponName()
{
	DWORD64 WeaponNameAddress = 0;
	char Buffer[256]{};
	
	WeaponNameAddress = memoryManager.TraceAddress(this->Address + Offset.Pawn.pClippingWeapon, { 0x10,0x20 ,0x0 });
	if (WeaponNameAddress == 0)
		return false;

	DWORD64 CurrentWeapon;
	short weaponIndex;
	Log::Debug("Entity.cpp 204		" + std::to_string(this->Address + Offset.Pawn.pClippingWeapon), true);
	memoryManager.ReadMemory(this->Address + Offset.Pawn.pClippingWeapon, CurrentWeapon);
	Log::Debug("Entity.cpp 206		" + std::to_string(CurrentWeapon + Offset.EconEntity.AttributeManager + Offset.WeaponBaseData.Item + Offset.WeaponBaseData.ItemDefinitionIndex), true);
	memoryManager.ReadMemory(CurrentWeapon + Offset.EconEntity.AttributeManager + Offset.WeaponBaseData.Item + Offset.WeaponBaseData.ItemDefinitionIndex, weaponIndex);

	if (weaponIndex == -1)
		return false;

	WeaponName = CEntity::GetWeaponName(weaponIndex);

	return true;
}

bool PlayerPawn::GetShotsFired()
{
	return GetDataAddressWithOffset<DWORD>(Address, Offset.Pawn.iShotsFired, this->ShotsFired);
}

bool PlayerPawn::GetAimPunchAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset.Pawn.aimPunchAngle, this->AimPunchAngle);
}

bool PlayerPawn::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Pawn.iTeamNum, this->TeamID);
}

bool PlayerPawn::GetAimPunchCache()
{
	return GetDataAddressWithOffset<C_UTL_VECTOR>(Address, Offset.Pawn.aimPunchCache, this->AimPunchCache);
}

DWORD64 PlayerController::GetPlayerPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset.Entity.PlayerPawn, this->Pawn))
		return 0;

	Log::Debug("Entity.cpp 243		" + std::to_string(gGame.GetEntityListAddress()), true);
	if (!memoryManager.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	Log::Debug("Entity.cpp 246		" + std::to_string(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9)), true);
	if (!memoryManager.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	Log::Debug("Entity.cpp 250		" + std::to_string(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF)), true);
	if (!memoryManager.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}

bool PlayerPawn::GetPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset.Pawn.Pos, this->Pos);
}

bool PlayerPawn::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Pawn.CurrentHealth, this->Health);
}

bool PlayerPawn::GetArmor()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Pawn.CurrentArmor, this->Armor);
}

bool PlayerPawn::GetAmmo()
{
	DWORD64 ClippingWeapon = 0;
	Log::Debug("Entity.cpp 275		" + std::to_string(Address + Offset.Pawn.pClippingWeapon), true);
	if (!memoryManager.ReadMemory<DWORD64>(Address + Offset.Pawn.pClippingWeapon, ClippingWeapon))
		return false;

	return GetDataAddressWithOffset<int>(ClippingWeapon, Offset.WeaponBaseData.Clip1, this->Ammo);
}

bool PlayerPawn::GetMaxAmmo()
{
	DWORD64 ClippingWeapon = 0;
	DWORD64 WeaponData = 0;
	Log::Debug("Entity.cpp 286		" + std::to_string(Address + Offset.Pawn.pClippingWeapon), true);
	if (!memoryManager.ReadMemory<DWORD64>(Address + Offset.Pawn.pClippingWeapon, ClippingWeapon))
		return false;
	Log::Debug("Entity.cpp 289		" + std::to_string(ClippingWeapon + Offset.WeaponBaseData.WeaponDataPTR), true);
	if (!memoryManager.ReadMemory<DWORD64>(ClippingWeapon + Offset.WeaponBaseData.WeaponDataPTR, WeaponData))
		return false;

	return GetDataAddressWithOffset<int>(WeaponData, Offset.WeaponBaseData.MaxClip, this->MaxAmmo);
}

bool PlayerPawn::GetFov()
{
	DWORD64 CameraServices = 0;
	Log::Debug("Entity.cpp 299		" + std::to_string(Address + Offset.Pawn.CameraServices), true);
	if (!memoryManager.ReadMemory<DWORD64>(Address + Offset.Pawn.CameraServices, CameraServices))
		return false;
	return GetDataAddressWithOffset<int>(CameraServices, Offset.Pawn.iFovStart, this->Fov);
}

bool PlayerPawn::GetFFlags()
{
	return GetDataAddressWithOffset<int>(Address, Offset.Pawn.fFlags, this->fFlags);
}

bool PlayerPawn::GetDefusing()
{
	Log::Debug("Entity.cpp 312		" + std::to_string(Address + Offset.C4.m_bBeingDefused), true);
	return memoryManager.ReadMemory(Address + Offset.C4.m_bBeingDefused, this->isDefusing);
}

bool PlayerPawn::GetFlashDuration()
{
	Log::Debug("Entity.cpp 318		" + std::to_string(Address + Offset.Pawn.flFlashDuration), true);
	return memoryManager.ReadMemory(Address + Offset.Pawn.flFlashDuration, this->FlashDuration);
}

bool PlayerPawn::GetVelocity()
{
	Vec3 Velocity;
	Log::Debug("Entity.cpp 325		" + std::to_string(Address + Offset.Pawn.AbsVelocity), true);
	if (!memoryManager.ReadMemory(Address + Offset.Pawn.AbsVelocity, Velocity))
		return false;
	this->Speed = sqrt(Velocity.x * Velocity.x + Velocity.y * Velocity.y);
	return true;
}

bool CEntity::IsAlive()
{
	return this->Controller.AliveStatus == 1 && this->Pawn.Health > 0;
}

bool CEntity::IsInScreen()
{
	return gGame.View.WorldToScreen(this->Pawn.Pos, this->Pawn.ScreenPos);
}

CBone CEntity::GetBone() const
{
	if (this->Pawn.Address == 0)
		return CBone{};
	return this->Pawn.BoneData;
}

bool Client::GetSensitivity()
{
	DWORD64 dwSensitivity;
	float flSensitivity;
	Log::Debug("Entity.cpp 353		" + std::to_string(gGame.GetClientDLLAddress() + Offset.Sensitivity), true);
	memoryManager.ReadMemory(gGame.GetClientDLLAddress() + Offset.Sensitivity, dwSensitivity);
	Log::Debug("Entity.cpp 355		" + std::to_string(dwSensitivity + 0x40), true);
	if (memoryManager.ReadMemory(dwSensitivity + 0x40, flSensitivity))
	{
		this->Sensitivity = flSensitivity;
		return true;
	}
	else
		return false;
}
