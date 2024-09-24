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

	return 0;
}