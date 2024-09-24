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
#include "../Core/MemoryManager.h"
#include "../Core/Offsets.h"

class Game
{
public:

	/// <summary>
/// Game constructor
/// </summary>
/// <returns> none </returns>
	Game();

	/// <summary>
/// Game destructor
/// </summary>
/// <returns> none </returns>
	~Game();

	/// <summary>
	/// Gets modules base and sets up basic game memory addresses
	/// </summary>
	/// <returns>0/1</returns>
	bool SetupAddress();

	/// <summary>
	/// Gets address
	/// </summary>
	/// <returns>address</returns>
	DWORD64 ClientDLL() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 ServerDLL() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 EntityList() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 Matrix() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 ViewAngle() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 EntityListEntry() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 LocalController() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 LocalPawn() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 ServerPawn() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 GlobalVars() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 JumpButton() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 AttackButton() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 RightButton() const;

	/// <summary>
/// Gets address
/// </summary>
/// <returns>address</returns>
	DWORD64 LeftButton() const;

	/// <summary>
	/// Updates entity list entry value
	/// </summary>
	/// <returns>0/1</returns>
	bool UpdateEntityListEntry();

private:

	DWORD64 _ServerDLL;
	DWORD64 _ClientDLL;
	DWORD64 _EntityList;
	DWORD64 _Matrix;
	DWORD64 _ViewAngle;
	DWORD64 _EntityListEntry;
	DWORD64 _LocalController;
	DWORD64 _LocalPawn;
	DWORD64 _ServerPawn;
	DWORD64 _GlobalVars;
	DWORD64 _JumpButton;
	DWORD64 _AttackButton;
	DWORD64 _RightButton;
	DWORD64 _LeftButton;
};

inline Game GameData;
