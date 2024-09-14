#pragma once
#include <chrono>
#include <iostream>
#include <utility>
#include <sstream>
#include <ctime>
#include <string>
#include "..\Game\Entity.h"
#include "..\Config\MenuConfig.hpp"

namespace bmb
{
	bool isPlanted = false;
	std::time_t plantTime;

	uint64_t currentTimeMillis() {
		using namespace std::chrono;
		return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	}

	int getBombSite(bool Planted)
	{
		if (Planted)
		{
			int site;
			uintptr_t cPlantedC4;
			//memoryManager.ReadMemory(gGame.GetClientDLLAddress() + Offset.PlantedC4, cPlantedC4);
			Log::Debug("bombtimer.h 28		" + std::to_string(gGame.GetClientDLLAddress() + Offset.PlantedC4), true);
			if (!memoryManager.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset.PlantedC4, cPlantedC4))
				return 0;
			Log::Debug("bombtimer.h 31		" + std::to_string(cPlantedC4), true);
			if (!memoryManager.ReadMemory<uintptr_t>(cPlantedC4, cPlantedC4))
				return 0;
			Log::Debug("bombtimer.h 34		" + std::to_string(cPlantedC4 + Offset.C4.m_nBombSite), true);
			if (!memoryManager.ReadMemory<int>(cPlantedC4 + Offset.C4.m_nBombSite, site))
				return 0;

			return site;
		}
		else
			return 0;
		
	}

	void RenderWindow(int inGame)
	{
		if ((!MiscCFG::bmbTimer || inGame == 0) && !(MiscCFG::bmbTimer && MenuConfig::ShowMenu))
			return;

		bool isBombPlanted;
		bool IsBeingDefused;
		float DefuseTime;
		auto plantedAddress = gGame.GetClientDLLAddress() + Offset.PlantedC4 - 0x8;

		Log::Debug("bobm.h 31		" + std::to_string(plantedAddress), true);
		memoryManager.ReadMemory(plantedAddress, isBombPlanted);

		auto time = currentTimeMillis();

		if (isBombPlanted && !isPlanted && (plantTime == NULL || time - plantTime > 60000))
		{
			isPlanted = true;
			plantTime = time;
		}

		//memoryManager.ReadMemory(Offset.PlantedC4 + Offset.C4.m_flDefuseCountDown, IsBeingDefused);
		//memoryManager.ReadMemory(Offset.PlantedC4 + Offset.C4.m_flDefuseCountDown, DefuseTime);

		if (!isPlanted && !MenuConfig::ShowMenu)
			return;

		static float windowWidth = 200.0f;
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
		ImGui::SetNextWindowPos({ (ImGui::GetIO().DisplaySize.x - 200.0f) / 2.0f, 80.0f }, ImGuiCond_Once);
		ImGui::SetNextWindowSize({ windowWidth, 0 }, ImGuiCond_Once);
		ImGui::GetStyle().WindowRounding = 8.0f;
		ImGui::Begin("Bomb Timer", nullptr, flags);
		float remaining = (40000 - (int64_t)time + plantTime) / (float)1000;

		/*
		if (remaining > 10 || remaining < 0 || !isPlanted)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 196, 0, 255));
		}
		else if (remaining > 5)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 155, 0, 255));
		}
		else {
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(242, 93, 93, 255));
		}*/

		ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 180) * 0.5f);
		float barLength = remaining <= 0.0f ? 0.0f : remaining >= 40 ? 1.0f : (remaining / 40.0f);
		
		if (isPlanted && remaining >= 0)
		{
			std::ostringstream ss;
			ss.precision(3);
			ss << "Bomb on " << (!getBombSite(isBombPlanted) ? "A" : "B") << ": " << std::fixed << remaining << " s";
			//std::ostringstream test;
			//test.precision(3);
			//test << IsBeingDefused << ", " << DefuseTime;
			Gui.MyText(std::move(ss).str().c_str(), true);
			//Gui.MyText(std::move(test).str().c_str(), true);
		}
		else {
			Gui.MyText("C4 not planted", true);
			barLength = 0.0f;
		}
		ImGui::TextUnformatted(" ");
		ImGui::SameLine();
		Gui.MyProgressBar(barLength, { 180, 15 }, "", MiscCFG::BombTimerCol);

		if (isPlanted && !isBombPlanted)
		{
			isPlanted = false;
		}
		//ImGui::PopStyleColor();
		ImGui::End();
	}
}