#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#pragma once
#include <iostream>
#include <string>
#include <windows.h>

namespace Lang
{
	
	inline struct Global
	{
		inline static const char* SwitchButton;
		inline static const char* FeatureSettings;
	} Global;

	inline struct ESPtext
	{
		inline static const char* Toggle;
		inline static const char* FeatureName;
		inline static const char* Box;
		inline static const char* BoxRounding;
		inline static const char* FilledBox;
		inline static const char* FilledAlpha;
		inline static const char* Skeleton;
		inline static const char* HeadBox;
		inline static const char* EyeRay;
		inline static const char* HealthBar;
		inline static const char* Weapon;
		inline static const char* Distance;
		inline static const char* PlayerName;
		inline static const char* SnapLine;
		inline static const char* LinePosList;
		inline static const char* VisCheck;
		inline static const char* Preview;
		inline static const char* CollapseHead;
		inline static const char* MultiColor;
		inline static const char* MultiColTip;
		inline static const char* Outline;
		inline static const char* BoxType;
		inline static const char* HealthNum;
		inline static const char* Ammo;
		inline static const char* ScopedESP;
		inline static const char* ShowArmorBar;
		inline static const char* ArmorNum;

		inline static const char* BoxType_Normal;
		inline static const char* BoxType_Edge;
		inline static const char* BoxType_Corner;
		inline static const char* BarType_Top;
		inline static const char* BarType_Vertical;
		inline static const char* HeadBoxType_Normal;
		inline static const char* HeadBoxType_Flat;
		inline static const char* LinePos_1;
		inline static const char* LinePos_2;
		inline static const char* LinePos_3;
	} ESPtext;

	inline struct AimbotText
	{
		inline static const char* Enable;
		inline static const char* FeatureName;
		inline static const char* HotKeyList;
		inline static const char* Toggle;
		inline static const char* DrawFov;
		inline static const char* VisCheck;
		inline static const char* JumpCheck;
		inline static const char* FovSlider;
		inline static const char* FovMinSlider;
		inline static const char* SmoothSlider;
		inline static const char* BoneList;
		inline static const char* Tip;
		inline static const char* ScopeOnly;
		inline static const char* BulletSlider;
		inline static const char* IgnoreFlash;

		inline static const char* Bone_1;
		inline static const char* Bone_2;
		inline static const char* Bone_3;
		inline static const char* Bone_4;
	} AimbotText;

	inline struct RCStext
	{
		inline static const char* Toggle;
		inline static const char* Yaw;
		inline static const char* Pitch;
	} RCStext;

	inline struct RadarText
	{
		inline static const char* Toggle;
		inline static const char* FeatureName;
		inline static const char* StyleList;
		inline static const char* CustomCheck;
		inline static const char* CrossLine;
		inline static const char* SizeSlider;
		inline static const char* ProportionSlider;
		inline static const char* RangeSlider;
		inline static const char* AlphaSlider;

		inline static const char* Style_1;
		inline static const char* Style_2;
		inline static const char* Style_3;
	} RadarText;

	inline struct TriggerText
	{
		inline static const char* Enable;
		inline static const char* FeatureName;
		inline static const char* HotKeyList;
		inline static const char* Toggle;
		inline static const char* ScopeOnly;
		inline static const char* DelaySlider;
		inline static const char* FakeShotSlider;
	} TriggerText;

	//inline struct CrosshairsText
	//{
	//	inline static const char* Toggle;
	//	inline static const char* FeatureName;
	//	inline static const char* PresetList;
	//	inline static const char* ColorEditor;
	//	inline static const char* Dot;
	//	inline static const char* DotSizeSlider;
	//	inline static const char* Outline;
	//	inline static const char* Crossline;
	//	inline static const char* hLengthSlider;
	//	inline static const char* vLengthSilder;
	//	inline static const char* GapSlider;
	//	inline static const char* ThicknessSlider;
	//	inline static const char* tStyle;
	//	inline static const char* Circle;
	//	inline static const char* RadiusSlider;
	//	inline static const char* TargetCheck;
	//	inline static const char* TeamCheck;
	//} CrosshairsText;

	inline struct MiscText
	{
		inline static const char* FeatureName;
		inline static const char* StyleList;
		inline static const char* HeadshotLine;
		inline static const char* SpecCheck;
		inline static const char* NoFlash;
		inline static const char* BunnyHop;
		//inline static const char* FastStop;
		inline static const char* SniperCrosshair;
		inline static const char* HitSound;
		inline static const char* HitMerker;
		inline static const char* bmbTimer;
		inline static const char* SpecList;
		inline static const char* Watermark;
		inline static const char* TeamCheck;
		inline static const char* AntiRecord;

		inline static const char* VisCheckDisable;
	} MiscText;

	inline struct ConfigText
	{
		inline static const char* FeatureName;
		inline static const char* Load;
		inline static const char* Save;
		inline static const char* Delete;
		inline static const char* Reset;
		inline static const char* Create;
		inline static const char* OpenFolder;
		inline static const char* SeparateLine;
		inline static const char* MyConfigs;
		inline static const char* AuthorName;
		inline static const char* ConfigName;
	} ConfigText;

	inline void English()
	{
		Global.SwitchButton = "Enable";
		Global.FeatureSettings = "Settings";

		// ESP
		ESPtext.Toggle = "Toggle";
		ESPtext.FeatureName = " ESP";
		ESPtext.Box = "Box";
		ESPtext.BoxRounding = "Box Rounding: ";
		ESPtext.FilledBox = "Filled Box";
		ESPtext.FilledAlpha = "Filled Box Alpha";
		ESPtext.Skeleton = "Skeleton";
		ESPtext.HeadBox = "Head ESP";
		ESPtext.EyeRay = "Eye Ray";
		ESPtext.HealthBar = "Health Bar";
		ESPtext.Weapon = "Weapon Icon";
		ESPtext.Distance = "Distance";
		ESPtext.PlayerName = "Player Name";
		ESPtext.SnapLine = "Snap Line";
		ESPtext.LinePosList = "Line Position: ";
		ESPtext.VisCheck = "Visible Color";
		ESPtext.Preview = "ESP Preview";
		ESPtext.MultiColor = "Multicoloured";
		ESPtext.MultiColTip = "Only work when the box has non-rounded corners.";
		ESPtext.Outline = "Outline";
		ESPtext.BoxType = "  Box Type";
		ESPtext.HealthNum = "Health Number";
		ESPtext.Ammo = "Ammo Bar";
		ESPtext.ScopedESP = "Show Scoped";
		ESPtext.ShowArmorBar = "Armor Bar";
		ESPtext.ArmorNum = "Armor Number";

		ESPtext.LinePos_1 = "Top";
		ESPtext.LinePos_2 = "Center";
		ESPtext.LinePos_3 = "Bottom";

		// Aimbot
		AimbotText.Enable = "Enable Aimbot";
		AimbotText.FeatureName = " Aimbot";
		AimbotText.HotKeyList = "Hotkey   ";
		AimbotText.Toggle = "Toggle Mode";
		AimbotText.DrawFov = "Show Fov";
		AimbotText.VisCheck = "Visible Check";
		AimbotText.JumpCheck = "On Ground Check";
		AimbotText.FovSlider = "FOV: ";
		AimbotText.FovMinSlider = "MiniFOV: ";
		AimbotText.SmoothSlider = "Smooth: ";
		AimbotText.BoneList = "Hitboxes";
		AimbotText.Tip = "Aimbot will not work while the menu is opened";
		AimbotText.ScopeOnly = "Scope Check";
		AimbotText.BulletSlider = "Start Bullet: ";
		AimbotText.IgnoreFlash = "Ignore Flash";

		// RCS
		RCStext.Toggle = "Recoil Control";
		RCStext.Yaw = "Yaw: ";
		RCStext.Pitch = "Pitch: ";

		// Radar
		RadarText.Toggle = "Show Radar";
		RadarText.FeatureName = " Radar";
		RadarText.StyleList = "Style";
		RadarText.CustomCheck = "Custom";
		RadarText.CrossLine = "Cross Line";
		RadarText.SizeSlider = "Point Size:";
		RadarText.ProportionSlider = "Proportion:";
		RadarText.RangeSlider = "Range:";
		RadarText.AlphaSlider = "Background Alpha:";

		// Triggerbot
		TriggerText.Enable = "Enable Triggerbot";
		TriggerText.FeatureName = " Triggerbot";
		TriggerText.HotKeyList = "Hotkey   ";
		TriggerText.Toggle = "Always Active";
		TriggerText.ScopeOnly = "Scope Check";
		TriggerText.DelaySlider = "Shot Delay:";
		TriggerText.FakeShotSlider = "Shot Duration:";

		// Crosshairs
		//CrosshairsText.Toggle = "Show Crosshairs";
		//CrosshairsText.FeatureName = " Crosshairs";
		//CrosshairsText.PresetList = "Presets";
		//CrosshairsText.ColorEditor = "Crosshairs Color";
		//CrosshairsText.Dot = "Center Dot";
		//CrosshairsText.DotSizeSlider = "Dot Size:";
		//CrosshairsText.Outline = "Crosshairs Outline";
		//CrosshairsText.Crossline = "Crossline";
		//CrosshairsText.hLengthSlider = "Horizontal Length:";
		//CrosshairsText.vLengthSilder = "Vertical Length:";
		//CrosshairsText.GapSlider = "Gap:";
		//CrosshairsText.ThicknessSlider = "Thickness:";
		//CrosshairsText.tStyle = "T Style";
		//CrosshairsText.Circle = "Circle";
		//CrosshairsText.RadiusSlider = "Circle Radius:";
		//CrosshairsText.TargetCheck = "Targeting Crosshairs";
		//CrosshairsText.TeamCheck = "TeamCheck";

		// Misc
		MiscText.FeatureName = " Misc";
		MiscText.StyleList = "Style";
		MiscText.HeadshotLine = "Headshot Line";
		MiscText.SpecCheck = "Work in Spec";
		MiscText.BunnyHop = "Bunny Hop";
		//MiscText.FastStop = "Fast Stop";
		MiscText.HitSound = "Hit Sound  ";
		MiscText.HitMerker = "Hit Markers";
		MiscText.bmbTimer = "Bomb Timer";
		MiscText.SpecList = "Spec List";
		MiscText.Watermark = "Watermark";
		MiscText.TeamCheck = "Team Check";
		MiscText.AntiRecord = "Anti Record";
		MiscText.SniperCrosshair = "Sniper Crosshair";
		MiscText.VisCheckDisable = "Visible Check DISABLED";


		// Config Menu
		ConfigText.FeatureName = "Config Loader";
		ConfigText.MyConfigs = "Config List";
		ConfigText.Load = "Load";
		ConfigText.Save = "Save";
		ConfigText.Delete = "Delete";
		ConfigText.Reset = "Reset";
		ConfigText.Create = "Create";
		ConfigText.OpenFolder = "Open Folder";
		ConfigText.SeparateLine = "Create Config";
		ConfigText.AuthorName = "Author Name";
		ConfigText.ConfigName = "Config Name";
	}
}
