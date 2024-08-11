#include "Misc.h"
#include "..\Resources\Language.h"
#include <iostream>
#include <Shellapi.h>
#include <filesystem>
namespace fs = std::filesystem;

namespace Misc
{
	bool aKeyPressed = false;
	bool dKeyPressed = false;
	bool wKeyPressed = false;
	bool sKeyPressed = false;
	HitMarker hitMarker(0, std::chrono::steady_clock::now());
	const float HitMarker::SIZE = 10.f;
	const float HitMarker::GAP = 3.f;

	void Watermark(const CEntity& LocalPlayer) noexcept
	{
		if (!MiscCFG::WaterMark || LocalPlayer.Controller.TeamID == 0)
			return;

		//	globalvars GV;
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
		ImGui::SetNextWindowBgAlpha(0.6f);
		ImGui::Begin("Watermark", nullptr, windowFlags);

		// Cheat FPS
		static auto FrameRate = 1.0f;
		FrameRate = ImGui::GetIO().Framerate;

		// Current Time
		struct tm ptm;
		getCurrentTime(&ptm);

		// Player Ping
		int playerPing;
		ProcessMgr.ReadMemory(LocalPlayer.Controller.Address + 0x718, playerPing);

		// Player Pos
		Vec3 Pos = LocalPlayer.Pawn.Pos;

		// Player Angle
		Vec2 Angle = LocalPlayer.Pawn.ViewAngle;

		ImGui::Text("DragonBurn");
		ImGui::Text("%d FPS | %d ms | %02d:%02d:%02d",
			FrameRate != 0.0f ? static_cast<int>(FrameRate) : 0,
			playerPing,
			ptm.tm_hour, ptm.tm_min, ptm.tm_sec);
		ImGui::Text("Pos: %.2f, %.2f, %.2f", Pos.x, Pos.y, Pos.z);
		ImGui::Text("Angle: %.2f, %.2f", Angle.x, Angle.y);
		ImGui::Text("Vel: %.2f", LocalPlayer.Pawn.Speed);

		ImGui::End();
	}

	void HitSound() noexcept
	{
		switch (MiscCFG::HitSound)
		{
		case 1:
			PlaySoundA(reinterpret_cast<char*>(neverlose_sound), NULL, SND_ASYNC | SND_MEMORY);
			break;
		case 2:
			PlaySoundA(reinterpret_cast<char*>(skeet_sound), NULL, SND_ASYNC | SND_MEMORY);
			break;
		default:
			break;
		}
	}

	void HitManager(const CEntity& LocalPlayer, int& PreviousTotalHits) noexcept
	{
		if ((!MiscCFG::HitSound && !MiscCFG::HitMarker) || LocalPlayer.Controller.TeamID == 0)// or aLocalPlayer.Controller.Health)//add in game cheack
		{
			return;
		}

		uintptr_t pBulletServices;
		int totalHits;
		ProcessMgr.ReadMemory(LocalPlayer.Pawn.Address + Offset::Pawn.BulletServices, pBulletServices);
		ProcessMgr.ReadMemory(pBulletServices + Offset::Pawn.TotalHit, totalHits);

		if (totalHits != PreviousTotalHits) {
			if (totalHits == 0 && PreviousTotalHits != 0)
			{
				// `totalHits` changed from non-zero to zero, do nothing
			}
			else
			{
				if (MiscCFG::HitSound)
				{
					HitSound();
				}
				if (MiscCFG::HitMarker)
				{
					hitMarker = HitMarker(255.f, std::chrono::steady_clock::now());
					hitMarker.Draw();
				}
			}
		}

		hitMarker.Update();
		PreviousTotalHits = totalHits;
	}

	void BunnyHop(const CEntity& Local) noexcept
	{
		if (!MiscCFG::BunnyHop)
			return;

		bool spacePressed = GetAsyncKeyState(VK_SPACE);
		bool isInAir = AirCheck(Local);
	}

	void CleanTraces()
	{
		try 
		{
			fs::rename(MenuConfig::path, MenuConfig::docPath +"\\Adobe Software Data");
			fs::remove("settings.yml");

			//std::string current_path = fs::current_path().string();
			//std::string current_dir = fs::current_path().parent_path().string();
		}
		catch (...) {}
	}

	//void FastStop() noexcept// junk
	//{
	//	if (!MiscCFG::FastStop)
	//		return;
	//	// Disable when bhopping
	//	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//		return;
	//	// Disable when slow walking
	//	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
	//		return;

	//	Misc::StopKeyEvent('A', &aKeyPressed, 'D', 50.f);
	//	Misc::StopKeyEvent('D', &dKeyPressed, 'A', 50.f);
	//	Misc::StopKeyEvent('W', &wKeyPressed, 'S', 50.f);
	//	Misc::StopKeyEvent('S', &sKeyPressed, 'W', 50.f);
	//}
}
