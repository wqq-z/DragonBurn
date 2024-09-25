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
#include <string>
#include <imgui.h>

// all program config data
namespace CFG
{
	// global config data
	namespace Global 
	{
		inline const std::string name = "DragonBurn";
		inline const std::string version = "2.0.4.0";
		inline const std::string author = "ByteCorum";
	}

	// core config data
	namespace Core 
	{
		inline std::string documentPath;
	}

	namespace Features 
	{
		namespace Visual
		{
			inline bool visual;
			inline bool frame;
			inline int frameType;
			inline bool outline;
			inline bool visible;

			inline bool bones;
			inline bool head;
			inline bool eyeRay;
			
			inline bool healthBar;
			inline bool healthNum;
			inline bool armorBar;
			inline bool armorNum;
			inline bool ammoBar;

			inline bool weapon;
			inline bool name;
			inline bool scope;
			inline bool distance;

			inline ImColor frameColor;
			inline ImColor visibleColor;
			inline ImColor bonesColor;
			inline ImColor headColor;
			inline ImColor eyeRayColor;
		}
		
		namespace Radar
		{
			inline bool radar;
			inline float range;
			inline float proportion;
			inline float pointSize;
		}

		namespace LegitBot
		{
			namespace Aimbot
			{
				inline bool aimBot;
				inline bool toggleMode;
				inline int hotKey;
				inline int startBullet;
				inline float fov;
				inline bool drawFov;
				inline float smooth;
				inline std::vector<int> hitboxes;
				inline bool visibleCheck;
				inline bool flashCheck;
				inline bool scopeCheck;
			}

			namespace RecoilControl
			{
				inline bool recoilControl;
				inline int startBullet;
				inline ImVec2 scale;
			}

			namespace Triggerbot
			{
				inline bool triggerBot;
				inline bool toggleMode;
				inline int hotKey;
				inline int delay;
				inline int duration;
				inline bool flashCheck;
				inline bool scopeCheck;
			}
		}

		namespace Misc
		{
			//add misc cfg
		}

		//add other cfg namespaces
	}
}