#pragma once
#include <iostream>
#include <Windows.h>
#include <Tlhelp32.h>
#include <string>
#include <vector>

#define DRAGON_DEVICE 0x8000
#define IOCTL_READ_PROCESS_MEMORY CTL_CODE(DRAGON_DEVICE, 0x4472, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PROCESS_MEMORY CTL_CODE(DRAGON_DEVICE, 0x4482, METHOD_NEITHER, FILE_ANY_ACCESS)


class MemoryMgr
{
public:
	MemoryMgr();
	~MemoryMgr();

	bool ConnectDriver(const LPCWSTR);
	bool DisconnectDriver();

	bool Attach(const DWORD);

    template <typename ReadType>
    bool ReadMemory(DWORD64 address, ReadType& value, SIZE_T size = sizeof(ReadType))
    {
        if (kernelDriver != nullptr && ProcessID != 0)
        {
            READ_PACK readPack;
            readPack.ProcessId = ProcessID;
            readPack.AddressToRead = reinterpret_cast<PVOID>(address);
            readPack.Buffer = &value;
            readPack.NumberOfBytesToRead = size;

            DWORD bytesReturned;
            BOOL result = DeviceIoControl(kernelDriver,
                IOCTL_READ_PROCESS_MEMORY,
                &readPack,
                sizeof(readPack),
                &readPack,
                sizeof(readPack),
                &bytesReturned,
                nullptr);

            return result == TRUE && bytesReturned == size;
        }
        return false;
    }

    //template <typename WriteType>
    //bool WriteMemory(DWORD64 address, WriteType& value, SIZE_T size = sizeof(WriteType))
    //{
    //    if (kernelDriver != INVALID_HANDLE_VALUE && ProcessID != 0)
    //    {
    //        WRITE_PACK writePack;
    //        writePack.ProcessId = ProcessID;
    //        writePack.AddressToWrite = reinterpret_cast<PVOID>(address);
    //        writePack.Buffer = const_cast<void*>(value);
    //        writePack.NumberOfBytesToWrite = size;

    //        DWORD bytesReturned;
    //        BOOL result = DeviceIoControl(kernelDriver,
    //            IOCTL_WRITE_PROCESS_MEMORY,
    //            &writePack,
    //            sizeof(writePack),
    //            nullptr,
    //            0,
    //            &bytesReturned,
    //            nullptr);

    //        return result == TRUE;
    //    }
    //    return false;
    //}

	DWORD64 TraceAddress(DWORD64, std::vector<DWORD>);

	static DWORD GetProcessID(const wchar_t*);
	static DWORD64 GetModuleBase(const DWORD, const wchar_t*);

private:
	DWORD ProcessID;
	HANDLE kernelDriver;

    // Structure for writing memory to a process
    typedef struct _WRITE_PACK {
        UINT32 ProcessId;
        PVOID AddressToWrite;
        SIZE_T NumberOfBytesToWrite;
        PVOID Buffer;
    } WRITE_PACK, * P_WRITE_PACK;

    // Structure for reading memory from a process
    typedef struct _READ_PACK {
        UINT32 ProcessId;
        PVOID AddressToRead;
        SIZE_T NumberOfBytesToRead;
        PVOID Buffer;
    } READ_PACK, * P_READ_PACK;

};

inline MemoryMgr memoryManager;

