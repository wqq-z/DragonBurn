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

#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::SetupAddress()
{
	this->_ClientDLL = MemoryMgr.GetModuleBase(L"client.dll");
	this->_ServerDLL = MemoryMgr.GetModuleBase(L"server.dll");

	this->_EntityList = ClientDLL() + Offset.EntityList;
	this->_Matrix = ClientDLL() + Offset.Matrix;
	this->_ViewAngle = ClientDLL() + Offset.ViewAngle;
	this->_LocalController = ClientDLL() + Offset.LocalPlayerController;
	this->_LocalPawn = ClientDLL() + Offset.LocalPlayerPawn;
	this->_ServerPawn = ServerDLL() + Offset.LocalPlayerPawn;
	this->_GlobalVars = ClientDLL() + Offset.GlobalVars;
	this->_JumpButton = ClientDLL() + Offset.Buttons.Jump;
	this->_AttackButton = ClientDLL() + Offset.Buttons.Attack;
	this->_RightButton = ClientDLL() + Offset.Buttons.Right;
	this->_LeftButton = ClientDLL() + Offset.Buttons.Left;

	return this->_ClientDLL != 0;
}

DWORD64 Game::ClientDLL() const
{
	return this->_ClientDLL;
}

DWORD64 Game::ServerDLL() const
{
	return this->_ServerDLL;
}

DWORD64 Game::EntityList() const
{
	return this->_EntityList;
}

DWORD64 Game::Matrix() const
{
	return this->_Matrix;
}

DWORD64 Game::ViewAngle() const
{
	return this->_ViewAngle;
}

DWORD64 Game::EntityListEntry() const
{
	return this->_EntityListEntry;
}

DWORD64 Game::LocalController() const
{
	return this->_LocalController;
}

DWORD64 Game::LocalPawn() const
{
	return this->_LocalPawn;
}

DWORD64 Game::ServerPawn() const
{
	return this->_ServerPawn;
}

DWORD64 Game::GlobalVars() const
{
	return this->_GlobalVars;
}

DWORD64 Game::JumpButton() const
{
	return this->_JumpButton;
}

DWORD64 Game::AttackButton() const
{
	return this->_AttackButton;
}

DWORD64 Game::RightButton() const
{
	return this->_RightButton;
}

DWORD64 Game::LeftButton() const
{
	return this->_LeftButton;
}

bool Game::UpdateEntityListEntry()
{
	DWORD64 EntityListEntry = 0;
	if (!MemoryMgr.ReadMemory(GameData.EntityList(), EntityListEntry))
		return false;
	if (!MemoryMgr.ReadMemory(EntityListEntry + 0x10, EntityListEntry))
		return false;

	this->_EntityListEntry = EntityListEntry;

	return this->_EntityListEntry != 0;
}