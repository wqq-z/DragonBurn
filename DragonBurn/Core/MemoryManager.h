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

#pragma once
#include <Windows.h>
#include <string>
#include <vector>

//IOCTL codes to communicate with kernel driver
#define DRAGON_DEVICE 0x8000
#define IOCTL_GET_PID CTL_CODE(DRAGON_DEVICE, 0x4452, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_GET_MODULE_BASE CTL_CODE(DRAGON_DEVICE, 0x4462, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_READ_PROCESS_MEMORY CTL_CODE(DRAGON_DEVICE, 0x4472, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PROCESS_MEMORY CTL_CODE(DRAGON_DEVICE, 0x4482, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PROCESS_MEMORY_PROTECTED CTL_CODE(DRAGON_DEVICE, 0x4492, METHOD_NEITHER, FILE_ANY_ACCESS)

class MemoryManager
{
public:
    /// <summary>
    /// MemoryManager constructor
    /// </summary>
    /// <returns> none </returns>
    MemoryManager();

    /// <summary>
    /// MemoryManager destructor
    /// </summary>
    /// <returns> none </returns>
    ~MemoryManager();

    /// <summary>
    /// Sets up communication with kernel driver
    /// </summary>
    /// <param name="driver name"></param>
    /// <returns>0/1</returns>
    bool ConnectDriver(const LPCWSTR&);

    /// <summary>
    /// Ends communication with kernel driver
    /// </summary>
    /// <returns>0/1</returns>
    bool DisconnectDriver();

    /// <summary>
    /// Attachs to process by pid
    /// </summary>
    /// <param name="PID"></param>
    /// <returns>0/1</returns>
    bool Attach(const DWORD&);

    /// <summary>
    /// Gets PID by name using request to kernel
    /// </summary>
    /// <param name="Process name"></param>
    /// <returns>PID</returns>
    DWORD GetProcessID(const wchar_t*) const;

    /// <summary>
    /// Gets Module base by name using request to kernel
    /// </summary>
    /// <param name="Module name"></param>
    /// <returns>Module base</returns>
    DWORD64 GetModuleBase(const wchar_t*) const;

    /// <summary>
    /// Reads process memory using request to kernel
    /// </summary>
    /// <typeparam name="Type for reading"></typeparam>
    /// <param name="Address"></param>
    /// <param name="Buffer to write"></param>
    /// <param name="Size to read"></param>
    /// <returns>0/1</returns>
    template <typename ReadType>
    bool ReadMemory(const DWORD64& address, ReadType& value, SIZE_T size = sizeof(ReadType)) const
    {
        if (kernelDriver != nullptr && ProcessID != 0)
        {
            READ_PACK ReadPack;
            ReadPack.pid = ProcessID;
            ReadPack.address = reinterpret_cast<PVOID>(address);
            ReadPack.buff = &value;
            ReadPack.size = size;

            BOOL result = DeviceIoControl(kernelDriver,
                IOCTL_READ_PROCESS_MEMORY,
                &ReadPack,
                sizeof(ReadPack),
                &ReadPack,
                sizeof(ReadPack),
                nullptr,
                nullptr);

            return result == TRUE; // && bytesReturned == size
        }
        return false;
    }

    /// <summary>
    /// Traces all address from vector
    /// </summary>
    /// <param name="Base Address"></param>
    /// <param name="Offsets vector"></param>
    /// <returns>correct address</returns>
    DWORD64 TraceAddress(const DWORD64&, const std::vector<DWORD>&) const;

private:
    DWORD ProcessID;
    HANDLE kernelDriver;

    // Structure for getting pid by name
    typedef struct _PID_PACK
    {
        UINT32 pid;
        WCHAR name[1024];
    } PID_PACK, * P_PID_PACK;

    // Structure for getting module address base
    typedef struct _MODULE_PACK {
        UINT32 pid;
        UINT64 baseAddress;
        SIZE_T size;
        WCHAR moduleName[1024];
    } MODULE_PACK, * P_MODULE_PACK;

    // Structure for writing memory to a process
    typedef struct _WRITE_PACK {
        UINT32 pid;
        PVOID address;
        SIZE_T size;
        PVOID buff;
    } WRITE_PACK, * P_WRITE_PACK;

    // Structure for reading memory from a process
    typedef struct _READ_PACK
    {
        UINT32 pid;
        PVOID address;
        SIZE_T size;
        PVOID buff;
    } READ_PACK, * P_READ_PACK;

};

inline MemoryManager MemoryMgr;


