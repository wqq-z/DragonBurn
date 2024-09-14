#pragma once
#include <Windows.h>
#include "MemoryMgr.h"

template <typename T>
inline bool GetDataAddressWithOffset(const DWORD64& Address, DWORD Offset, T& Data)
{
	if (Address == 0)
		return false;

	Log::Debug("globals.hpp 11		" + std::to_string(Address + Offset), true);
	if (!memoryManager.ReadMemory<T>(Address + Offset, Data))
		return false;

	return true;
}