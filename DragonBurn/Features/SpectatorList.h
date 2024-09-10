#pragma once
#include "..\Config\MenuConfig.hpp"
#include "..\Game\Entity.h"
#include <vector>
#include <string>
#include <iostream>

namespace SpecList
{
    void SpectatorWindowList(const CEntity& LocalEntity)
    {
        if (!MiscCFG::SpecList || LocalEntity.Controller.TeamID == 0)
            return;

        static float windowWidth = 120.0f;
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowPos({ 10.0f, ImGui::GetIO().DisplaySize.y / 2 - 200 }, ImGuiCond_Once);
        ImGui::SetNextWindowSize({ windowWidth, (float)LocalEntity.Controller.spectators.size() * 5 });
        ImGui::GetStyle().WindowRounding = 8.0f;

        if (ImGui::Begin("Spectators", NULL, flags))
        {

            float lineSpacing = -15.0f;


            for (const auto& spectator : LocalEntity.Controller.spectators)
            {
                ImGui::SetCursorPosY(ImGui::GetCursorPosX() + 5);
                ImGui::TextColored(ImColor(0, 255, 0, 255), spectator.c_str());
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + lineSpacing);
            }


            ImGui::End();
        }
    }

    uintptr_t getAddressBase(uintptr_t entityList, uintptr_t playerPawn)
    {
        uintptr_t listEntrySecond;
        ProcessMgr.ReadMemory<uintptr_t>(entityList + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16, listEntrySecond);

        uintptr_t isPawn;
        ProcessMgr.ReadMemory<uintptr_t>(listEntrySecond + 120 * (playerPawn & 0x1FF), isPawn);

        return listEntrySecond == 0 ? 0 : isPawn;
    }

    void GetSpectatorList(CEntity Entity, CEntity& LocalEntity)
    {
        if (!MiscCFG::SpecList || LocalEntity.Controller.TeamID == 0)
            return;

        LocalEntity.Controller.spectators.empty();
        std::cout << Entity.Controller.PlayerName << '\n';

        uintptr_t LocalPlayer;
        ProcessMgr.ReadMemory<uintptr_t>(gGame.GetClientDLLAddress() + Offset.LocalPlayerController, LocalPlayer);
        uintptr_t localPlayerPawn;
        ProcessMgr.ReadMemory<uintptr_t>(LocalPlayer + Offset.PlayerController.m_hPawn, localPlayerPawn);

        uintptr_t CSlocalPlayerPawn;
        ProcessMgr.ReadMemory<uintptr_t>(gGame.GetEntityListEntry() + 120 * (localPlayerPawn & 0x1FF), CSlocalPlayerPawn);

        uint32_t spectatorPawn;
        ProcessMgr.ReadMemory<uint32_t>(Entity.Controller.Address + Offset.PlayerController.m_hPawn, spectatorPawn);

        uintptr_t entityList;
        ProcessMgr.ReadMemory<uintptr_t>(gGame.GetEntityListAddress(),entityList);

        uintptr_t pawn = getAddressBase(entityList, spectatorPawn);

        uintptr_t observed;
        ProcessMgr.ReadMemory<uintptr_t>(pawn + Offset.PlayerController.m_pObserverServices, observed);
        std::cout << "observed: " << observed << '\n';

        uint64_t observedTarget;
        ProcessMgr.ReadMemory<uintptr_t>(observed + Offset.PlayerController.m_hObserverTarget, observedTarget);
        std::cout << "observedTarget: " << observedTarget << '\n';

        uintptr_t spectatorTarget = getAddressBase(entityList, observedTarget);
        std::cout << "handle: " << spectatorTarget << '\n';
        if (observed)
        {
            if (spectatorTarget == CSlocalPlayerPawn)
            {
                LocalEntity.Controller.spectators.push_back(Entity.Controller.PlayerName);
            }
        }
        std::cout << "\n\n\n";
    }
}