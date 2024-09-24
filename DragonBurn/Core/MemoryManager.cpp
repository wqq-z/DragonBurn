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

#include "MemoryManager.h"

MemoryManager::MemoryManager()
{
	ProcessID = 0;
	kernelDriver = nullptr;
}

MemoryManager::~MemoryManager()
{
	DisconnectDriver();

	ProcessID = 0;
	kernelDriver = nullptr;
}

bool MemoryManager::ConnectDriver(const LPCWSTR name)
{
	kernelDriver = CreateFile(name, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (kernelDriver == INVALID_HANDLE_VALUE)
		return false;

	return true;
}

bool MemoryManager::DisconnectDriver()
{
	if (kernelDriver != nullptr)
	{
		return CloseHandle(kernelDriver);
	}
	else
		return false;
}

bool MemoryManager::Attach(const DWORD pid)
{
	if (pid == 0)
		return false;

	ProcessID = pid;
	return true;
}

DWORD MemoryManager::GetProcessID(const wchar_t* processName)
{
	if (kernelDriver != nullptr)
	{
		PID_PACK PidPack;
		RtlZeroMemory(PidPack.name, 1024);
		wcsncpy(PidPack.name, processName, 1024);

		BOOL result = DeviceIoControl(kernelDriver,
			IOCTL_GET_PID,
			&PidPack,
			sizeof(PidPack),
			&PidPack,
			sizeof(PidPack),
			nullptr,
			nullptr);

		if (result == TRUE)
			return PidPack.pid;
		else
			return 0;
	}
	else
		return 0;
}

DWORD64 MemoryManager::GetModuleBase(const wchar_t* moduleName)
{
	if (kernelDriver != nullptr && ProcessID != 0)
	{
		MODULE_PACK ModulePack;
		DWORD64 address = 0;
		ModulePack.pid = ProcessID;
		ModulePack.baseAddress = address;
		RtlZeroMemory(ModulePack.moduleName, 1024);
		wcsncpy(ModulePack.moduleName, moduleName, 1024);

		BOOL result = DeviceIoControl(kernelDriver,
			IOCTL_GET_MODULE_BASE,
			&ModulePack,
			sizeof(ModulePack),
			&ModulePack,
			sizeof(ModulePack),
			nullptr,
			nullptr);

		if (result == TRUE)
			return ModulePack.baseAddress;
		else
			return 0;
	}
	else
		return 0;
}

DWORD64 MemoryManager::TraceAddress(DWORD64 baseAddress, std::vector<DWORD> offsets)
{
	if (kernelDriver != nullptr && ProcessID != 0)
	{
		DWORD64 address = 0;

		if (offsets.size() == 0)
			return baseAddress;

		if (!ReadMemory<DWORD64>(baseAddress, address))
			return 0;

		for (int i = 0; i < offsets.size() - 1; i++)
		{
			if (!ReadMemory<DWORD64>(address + offsets[i], address))
				return 0;
		}
		return address == 0 ? 0 : address + offsets[offsets.size() - 1];
	}
	else
		return 0;
}

//template <typename WriteType>
//bool WriteMemory(DWORD64 address, WriteType& value, SIZE_T size = sizeof(WriteType))
//{
//    if (kernelDriver != INVALID_HANDLE_VALUE && ProcessID != 0)
//    {
//        WRITE_PACK WritePack;
//        WritePack.pid = ProcessID;
//        WritePack.address = reinterpret_cast<PVOID>(address);
//        WritePack.buff = const_cast<void*>(value);
//        WritePack.size = size;

//        BOOL result = DeviceIoControl(kernelDriver,
//            IOCTL_WRITE_PROCESS_MEMORY,
//            &WritePack,
//            sizeof(WritePack),
//            nullptr,
//            0,
//            nullptr,
//            nullptr);

//        return result == TRUE;
//    }
//    return false;
//}

//template <typename WriteType>
//bool WriteMemoryProtected(DWORD64 address, WriteType& value, SIZE_T size = sizeof(WriteType))
//{
//    if (kernelDriver != INVALID_HANDLE_VALUE && ProcessID != 0)
//    {
//        WRITE_PACK WritePack;
//        WritePack.pid = ProcessID;
//        WritePack.address = reinterpret_cast<PVOID>(address);
//        WritePack.buff = const_cast<void*>(value);
//        WritePack.size = size;

//        BOOL result = DeviceIoControl(kernelDriver,
//            IOCTL_WRITE_PROCESS_MEMORY_PROTECTED,
//            &WritePack,
//            sizeof(WritePack),
//            nullptr,
//            0,
//            nullptr,
//            nullptr);

//        return result == TRUE;
//    }
//    return false;
//}