#include "MemoryMgr.h"
#include "../Helpers/Logger.h"

MemoryMgr::MemoryMgr() 
{
	ProcessID = 0;
	kernelDriver = nullptr;
}

MemoryMgr::~MemoryMgr() 
{
	Detach();
	DisconnectDriver();

	ProcessID = 0;
	kernelDriver = nullptr;
}

bool MemoryMgr::ConnectDriver(const LPCWSTR name)
{
	kernelDriver = CreateFile(name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (kernelDriver == INVALID_HANDLE_VALUE)
		return false;

	return true;
}

bool MemoryMgr::DisconnectDriver() 
{
	if (kernelDriver != nullptr)
	{
		return CloseHandle(kernelDriver);
	}
	else
		return false;
}

bool MemoryMgr::Attach(const DWORD pid)
{
	Request req;
	req.pid = reinterpret_cast<HANDLE>(pid);
	ProcessID = pid;

	return DeviceIoControl(kernelDriver, kernelCodes::ATTACH, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
}

bool MemoryMgr::Detach() 
{
	if (kernelDriver != nullptr && ProcessID != 0)
	{
		Request req;
		req.pid = reinterpret_cast<HANDLE>(ProcessID);
		ProcessID = 0;

		return DeviceIoControl(kernelDriver, kernelCodes::DETACH, &req, sizeof(req), &req, sizeof(req), nullptr, nullptr);
	}
	else
		return false;
}

DWORD64 MemoryMgr::TraceAddress(DWORD64 baseAddress, std::vector<DWORD> offsets)
{
	if (kernelDriver != nullptr && ProcessID != 0)
	{
		DWORD64 address = 0;

		if (offsets.size() == 0)
			return baseAddress;

		Log::Debug("MemoryMgr.cpp 70		" + std::to_string(baseAddress), true);
		if (!ReadMemory<DWORD64>(baseAddress, address))
			return 0;

		for (int i = 0; i < offsets.size() - 1; i++)
		{
			Log::Debug("MemoryMgr.cpp 76		" + std::to_string(address + offsets[i]), true);
			if (!ReadMemory<DWORD64>(address + offsets[i], address))
				return 0;
		}
		return address == 0 ? 0 : address + offsets[offsets.size() - 1];
	}
	else
		return 0;
}

DWORD MemoryMgr::GetProcessID(const wchar_t* processName) 
{
	DWORD processId = 0;
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (snapShot == INVALID_HANDLE_VALUE)
		return processId;

	PROCESSENTRY32W entry = {};
	entry.dwSize = sizeof(decltype(entry));

	if (Process32FirstW(snapShot, &entry) == TRUE) // Check if the first handle is the one we want
	{
		if (_wcsicmp(processName, entry.szExeFile) == 0)
			processId = entry.th32ProcessID;

		else
		{
			while (Process32NextW(snapShot, &entry) == TRUE)
			{
				if (_wcsicmp(processName, entry.szExeFile) == 0)
				{
					processId = entry.th32ProcessID;
					break;
				}
			}
		}
	}

	CloseHandle(snapShot);
	return processId;
}

DWORD64 MemoryMgr::GetModuleBase(const DWORD pid, const wchar_t* moduleName) {
	DWORD64 moduleBase = 0;

	// Snap-shot of process' modules (dlls).
	HANDLE snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
	if (snapShot == INVALID_HANDLE_VALUE)
		return moduleBase;

	MODULEENTRY32W entry = {};
	entry.dwSize = sizeof(decltype(entry));

	if (Module32FirstW(snapShot, &entry) == TRUE)
	{
		if (wcsstr(moduleName, entry.szModule) != nullptr)
			moduleBase = reinterpret_cast<DWORD64>(entry.modBaseAddr);

		else
		{
			while (Module32NextW(snapShot, &entry) == TRUE)
			{
				if (wcsstr(moduleName, entry.szModule) != nullptr)
				{
					moduleBase = reinterpret_cast<DWORD64>(entry.modBaseAddr);
					break;
				}
			}
		}
	}

	CloseHandle(snapShot);
	return moduleBase;
}
