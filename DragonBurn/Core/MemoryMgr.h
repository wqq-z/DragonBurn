#pragma once
#include <iostream>
#include <Windows.h>
#include <Tlhelp32.h>
#include <string>
#include <vector>

namespace kernelCodes
{
	inline const ULONG ATTACH = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4462, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	inline const ULONG READ = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4472, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	inline const ULONG WRITE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4482, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	inline const ULONG DETACH = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4492, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
}

class MemoryMgr
{
public:
	MemoryMgr();
	~MemoryMgr();

	bool ConnectDriver(const LPCWSTR);
	bool DisconnectDriver();

	bool Attach(const DWORD);
	bool Detach();

	template <typename ReadType>
	bool ReadMemory(DWORD64 address, ReadType& value, int size = -1)
	{
		if (kernelDriver != nullptr && ProcessID != 0)
		{
			if (size == -1)
				size = sizeof(ReadType);

			Package pack;

			pack.address = reinterpret_cast<PVOID>(address);
			pack.buff = &value;
			pack.size = size;

			return DeviceIoControl(kernelDriver, kernelCodes::READ, &pack, sizeof(pack), &pack, sizeof(pack), nullptr, nullptr);
		}
		else
			return false;
	}

	DWORD64 TraceAddress(DWORD64, std::vector<DWORD>);

	static DWORD GetProcessID(const wchar_t*);
	static DWORD64 GetModuleBase(const DWORD, const wchar_t*);

private:
	DWORD ProcessID;
	HANDLE kernelDriver;

	struct Package
	{
		HANDLE __pid__;

		PVOID address;
		PVOID buff;

		SIZE_T size;
		SIZE_T callback_size;
	};

	//static struct
	//{
	//	static const ULONG ATTACH = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4462, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	//	static const ULONG READ = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4472, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	//	static const ULONG WRITE = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4482, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	//	static const ULONG DETACH = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4492, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
	//}Codes;

};

inline MemoryMgr memoryManager;

