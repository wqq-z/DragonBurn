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

#include "Helpers/Logger.h"
#include "Core/Setup.h"
#include "Core/Offsets.h"
#include "Core/MemoryManager.h"
#include "Game/Game.h"

/// <summary>
/// main program entry
/// </summary>
/// <param name="arguments count"></param>
/// <param name="arguments values"></param>
/// <returns> status </returns>
int main(int argc, char* argv[])
{
	ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
	SetConsoleTitle(L"DragonBurn");
	Logger Log = Logger(GetStdHandle(STD_OUTPUT_HANDLE));

	Log.Custom(R"LOGO(______                            ______                  
|  _  \                           | ___ \                 
| | | |_ __ __ _  __ _  ___  _ __ | |_/ /_   _ _ __ _ __  
| | | | '__/ _` |/ _` |/ _ \| '_ \| ___ \ | | | '__| '_ \ 
| |/ /| | | (_| | (_| | (_) | | | | |_/ / |_| | |  | | | |
|___/ |_|  \__,_|\__, |\___/|_| |_\____/ \__,_|_|  |_| |_|
                  __/ |                                   
                 |___/                                    
https://github.com/ByteCorum/DragonBurn


)LOGO", 13);

#ifndef _DEBUG
	Log.Info("Checking cheat version");
	switch (Setup::CheckProgVersion())
	{
	case 0:
		Log.PreviousLine();
		Log.Error("Bad internet connection");
		break;

	case 1:
		Log.PreviousLine();
		Log.Error("Failed to get current version");
		break;

	case 2:
		Log.PreviousLine();
		Log.Error("Your cheat version is outdated");
		break;

	case 3:
		Log.PreviousLine();
		Log.Fine("Your cheat version is up to date");
		break;

	default:

		Log.PreviousLine();
		Log.Error("Unknown connection error");
		break;

	}
#endif

	Log.Info("Updating offsets");
	switch (Offset.UpdateOffsets())
	{
	case 0:

		Log.PreviousLine();
		Log.Error("Bad internet connection");
		break;

	case 1:

		Log.PreviousLine();
		Log.Error("Failed to UpdateOffsets");
		break;

	case 2:
		Log.PreviousLine();
		Log.Fine("Offsets updated");
		break;

	default:

		Log.PreviousLine();
		Log.Error("Unknown connection error");
		break;

	}

	Log.Info("Connecting to kernel mode driver");
	if (MemoryMgr.ConnectDriver(L"\\\\.\\DragonBurn-kernel"))
	{
		Log.PreviousLine();
		Log.Fine("Successfully connected to kernel mode driver");
	}
	else
	{
		Log.PreviousLine();
		Log.Error("Failed to connect to kernel mode driver");
	}

	std::cout << '\n';
	bool preStart = false;
	while (MemoryMgr.GetProcessID(L"cs2.exe") == 0)
	{
		Log.PreviousLine();
		Log.Info("Waiting for CS2");
		preStart = true;
	}

	if (preStart)
	{
		Log.PreviousLine();
		Log.Info("Connecting to CS2(it may take some time)");
		Sleep(20000);
	}

	Log.PreviousLine();
	Log.Fine("Connected to CS2");
	Log.Info("Linking to CS2");

	if (!MemoryMgr.Attach(MemoryMgr.GetProcessID(L"cs2.exe")))
	{
		Log.PreviousLine();
		Log.Error("Failed to attach to the process");
	}

	if (!GameData.SetupAddress())
	{
		Log.PreviousLine();
		Log.Error("Failed to Init Address");
	}

	Log.PreviousLine();
	Log.Fine("Linked to CS2");

	return 0;
}