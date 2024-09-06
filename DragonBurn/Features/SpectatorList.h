#pragma once
#include "..\Config\MenuConfig.hpp"
#include "..\Game\Entity.h"
#include <vector>
#include <string>
#include <iostream>

namespace SpecList
{
    //float spectatorOffsetY = 0;
    //bool isSpectating(const uint32_t m_hPawn)
    //{
    //    uintptr_t pCSPlayerPawn, m_pObserverServices, m_hObserverTarget;
    //    ProcessMgr.ReadMemory<uintptr_t>(gGame.GetEntityListEntry() + 120 * (m_hPawn & 0x1FF), pCSPlayerPawn);
    //    ProcessMgr.ReadMemory<uintptr_t>(pCSPlayerPawn + 0x10C0, m_pObserverServices);
    //    ProcessMgr.ReadMemory<uintptr_t>(m_pObserverServices + 0x44, m_hObserverTarget);
    //    if (!m_hObserverTarget == 0) {
    //        //std::cout << m_hObserverTarget << std::endl;
    //        return true;
    //    }

    //    return false;
    //}

    void SpectatorWindowList(CEntity& LocalEntity)
    {
        if (!MiscCFG::SpecList || LocalEntity.Controller.TeamID == 0)
            return;

        static float windowWidth = 120.0f;
        ImGuiWindowFlags flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        ImGui::SetNextWindowPos({ 10.0f, ImGui::GetIO().DisplaySize.y/2-200}, ImGuiCond_Once);
        ImGui::SetNextWindowSize({ windowWidth, 0 }, ImGuiCond_Once);

        if (ImGui::Begin("Spectators", NULL, flags))
        {

            float lineSpacing = -15.0f;


            for (const auto& spectator : LocalEntity.Controller.spectators)
            {
                ImGui::TextColored(ImColor(0, 255, 0, 255), spectator.c_str());
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + lineSpacing);
            }


            ImGui::End();
        }
    }

    void GetSpectatorList(CEntity& Entity, CEntity& LocalEntity, DWORD64 EntityAddress)
    {
        if (!MiscCFG::SpecList || LocalEntity.Controller.TeamID == 0)
            return;

        //uintptr_t LocalPlayer = MemMan.ReadMem<uintptr_t>(baseAddy + offsets::clientDLL["dwLocalPlayerController"]);
        //uintptr_t localPlayerPawn = MemMan.ReadMem<uintptr_t>(LocalPlayer + clientDLL::clientDLLOffsets["CBasePlayerController"]["fields"]["m_hPawn"]);
        //uintptr_t list_entry2 = MemMan.ReadMem<uintptr_t>(entityList + 0x8 * ((localPlayerPawn & 0x7FFF) >> 9) + 16);
        //if (!list_entry2)
        //    return false;

        //const uintptr_t CSlocalPlayerPawn = MemMan.ReadMem<uintptr_t>(list_entry2 + 120 * (localPlayerPawn & 0x1FF));

        //if (localPlayer)
        //    return this->getSpectating() == CSlocalPlayerPawn;
        //return this->getSpectating() != 0;

        // LocalEntity.Controller.spectators.push_back(Entity.Controller.PlayerName);
        
        LocalEntity.Controller.spectators.empty();
        uint32_t m_hPawn;
        uintptr_t pCSPlayerPawn;
        uintptr_t m_pObserverServices;
        
        ProcessMgr.ReadMemory<uint32_t>(Entity.Controller.Address + 0x5DC, m_hPawn);
        ProcessMgr.ReadMemory<uintptr_t>(gGame.GetEntityListEntry() + 120 * (m_hPawn & 0x1FF), pCSPlayerPawn);
        ProcessMgr.ReadMemory<uintptr_t>(pCSPlayerPawn + 0x10C0, m_pObserverServices);
        std::cout << "SL" << '\n';

        if (m_pObserverServices)
        {
            std::cout << "Observed" << '\n';
            std::cout << LocalEntity.Pawn.Address << '\n';
            uint32_t m_hObserverTarget;
            uintptr_t list_entry;
            uintptr_t pController;
            ProcessMgr.ReadMemory<uint32_t>(m_pObserverServices + 0x44, m_hObserverTarget);
            ProcessMgr.ReadMemory<uintptr_t>(EntityAddress + 0x8 * ((m_hObserverTarget & 0x7FFF) >> 9) + 0x10, list_entry);
            ProcessMgr.ReadMemory<uintptr_t>(gGame.GetEntityListEntry() + 120 * (m_hObserverTarget & 0x1FF), pController);

            std::cout << "Player: " << Entity.Controller.PlayerName << " m_hObserverTarget: " << m_hObserverTarget << "list_entry: " << list_entry << "pController: " << pController << '\n';

            if (pController == LocalEntity.Pawn.Address)
            {
                LocalEntity.Controller.spectators.push_back(Entity.Controller.PlayerName);
                std::cout << Entity.Controller.PlayerName << '\n';
            }
        }
    }
}