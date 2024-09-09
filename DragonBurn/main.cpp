#define _CRT_SECURE_NO_WARNINGS
#include "Core/Cheats.h"
#include "Offsets/Offsets.h"
#include "Resources/Language.h"
#include "Core/Init.h"
#include "Config/ConfigSaver.hpp"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <KnownFolders.h>
#include <ShlObj.h>
#include <stdio.h>

using namespace std;

namespace fs = filesystem;
string fileName;

void Cheat();
void PreviousLine();
void Exit();

int main()
{
	Cheat();
}

void Cheat()
{
	ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
	srand(time(0));
	Init::Verify::RandTitle();

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 13);
	cout << R"LOGO(______                            ______                  
|  _  \                           | ___ \                 
| | | |_ __ __ _  __ _  ___  _ __ | |_/ /_   _ _ __ _ __  
| | | | '__/ _` |/ _` |/ _ \| '_ \| ___ \ | | | '__| '_ \ 
| |/ /| | | (_| | (_| | (_) | | | | |_/ / |_| | |  | | | |
|___/ |_|  \__,_|\__, |\___/|_| |_\____/ \__,_|_|  |_| |_|
                  __/ |                                   
                 |___/                                    )LOGO" << endl << endl << endl;

	if (!Init::Verify::CheckWindowVersion())
	{
		SetConsoleTextAttribute(hConsole, 14);
		cout << "[INFO] Your os is unsupported, bugs may occurred." << endl;
		system("pause");
	}

	SetConsoleTextAttribute(hConsole, 14);
	cout << "[INFO] Checking cheat version(it may take some time)..." << endl;
	switch (Init::Verify::CheckCheatVersion())
	{
	case 0:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Bad internet connection." << endl;
		Exit();

	case 1:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Failed to get current version." << endl;
		Exit();

	case 2:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Your cheat version is outdated." << endl;
		Exit();

	case 3:
		SetConsoleTextAttribute(hConsole, 14);
		PreviousLine();
		cout << "[INFO] Your cheat version is up to date." << endl;
		break;

	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Unknown connection error" << endl;
		Exit();

	}

	SetConsoleTextAttribute(hConsole, 14);
	cout << "[INFO] Updating offsets(it may take some time)..." << endl;
	switch (Offset.UpdateOffsets())
	{
	case 0:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Bad internet connection." << endl;
		Exit();

	case 1:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Failed to UpdateOffsets." << endl;
		Exit();

	case 2:
		SetConsoleTextAttribute(hConsole, 14);
		PreviousLine();
		cout << "[INFO] Offsets updated" << endl;
		break;

	default:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		PreviousLine();
		cout << "[ERROR] Unknown connection error" << endl;
		Exit();

	}
	std::cout << '\n';
	while (ProcessMgr.GetProcessID("cs2.exe") == 0)
	{
		PreviousLine();
		SetConsoleTextAttribute(hConsole, 14);
		cout << "[INFO] Waiting for CS2." << endl;
	}

	SetConsoleTextAttribute(hConsole, 14);
	PreviousLine();
	cout << "[INFO] Connecting to CS2(it may take some time)..." << endl;
	Sleep(20000);

	PreviousLine();
	cout << "[INFO] Connected to CS2" << endl;


	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	switch (ProcessStatus)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << "[ERROR] Game not found." << endl;
		Exit();
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << "[ERROR] Failed to hook process, please run the cheat as Administrator." << endl;
		Exit();
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << "[ERROR] Failed to get module address." << endl;
		Exit();
		break;
	default:
		break;
	}

	//switch (Init::Client::CheckCS2Version()) 
	//{
	//case 0:
	//	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	//	cout << "[ERROR] Failed to get the current game version." << endl;
	//	system("pause");
	//	break;

	//case 1:
	//	SetConsoleTextAttribute(hConsole, 14);
	//	cout << "[Info] This version of the cheat was made for a later version of the game and may work unstable on the current version." << endl;
	//	system("pause");
	//	break;

	//case 2:
	//	break;

	//default:
	//	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	//	cout << "[ERROR] Failed to get the current game version." << endl;
	//	system("pause");
	//	break;
	//}

	if (!gGame.InitAddress())
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
		cout << "[ERROR] Failed to Init Address." << endl;
		Exit();
	}

	SetConsoleTextAttribute(hConsole, 11);
	cout << "[Game] Process ID: " << ProcessMgr.ProcessID << endl;
	cout << "[Game] Client Address: " << gGame.GetClientDLLAddress() << endl;

	char documentsPath[MAX_PATH];
	if (SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath) != S_OK) {
		SetConsoleTextAttribute(hConsole, 12);
		cerr << "[ERROR] Failed to get the Documents folder path." << endl;
		Exit();
	}
	MenuConfig::path = documentsPath;
	MenuConfig::docPath = documentsPath;
	MenuConfig::path += "\\DragonBurn";

	if (fs::exists(MenuConfig::docPath + "\\Adobe Software Data"))
	{
		fs::rename(MenuConfig::docPath + "\\Adobe Software Data", MenuConfig::path);
	}

	if (fs::exists(MenuConfig::path))
	{
		SetConsoleTextAttribute(hConsole, 14);
		cout << "[Info] Config folder connected: " << MenuConfig::path << endl;
	}
	else
	{
		if (fs::create_directory(MenuConfig::path))
		{
			SetConsoleTextAttribute(hConsole, 14);
			cout << "[Info] Config folder created: " << MenuConfig::path << endl;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 12);
			cerr << "[ERROR] Failed to create the config directory." << endl;
			Exit();
		}
	}

	ifstream defaultConfig(MenuConfig::path + "\\default.cfg");
	if (defaultConfig.is_open())
	{
		MenuConfig::defaultConfig = true;
		defaultConfig.close();
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << "DragonBurn loaded!!!\nGLHF" << endl;
	Sleep(3000);
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		cout << e.what() << endl;
	}
}

void PreviousLine() 
{
	std::cout << "\033[1A\033[0G                                                                                \033[0G";
}

void Exit()
{
	system("pause");
	exit(0);
}