#pragma once
#include <ntifs.h>
#include "Logger.h"

// Define IOCTL codes for device communication
#define DRAGON_DEVICE 0x8000
#define IOCTL_READ_PROCESS_MEMORY CTL_CODE(DRAGON_DEVICE, 0x4472, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_WRITE_PROCESS_MEMORY CTL_CODE(DRAGON_DEVICE, 0x4482, METHOD_NEITHER, FILE_ANY_ACCESS)

extern "C" //undocumented windows internal functions (exported by ntoskrnl)
{
	NTKERNELAPI NTSTATUS IoCreateDriver(PUNICODE_STRING DriverName, PDRIVER_INITIALIZE InitializationFunction);
}
extern "C" NTSTATUS NTAPI MmCopyVirtualMemory(
    PEPROCESS SourceProcess,
    PVOID SourceAddress,
    PEPROCESS TargetProcess,
    PVOID TargetAddress,
    SIZE_T BufferSize,
    KPROCESSOR_MODE PreviousMode,
    PSIZE_T ReturnSize
);

namespace Kernel 
{
	NTSTATUS DriverIrpCreate(PDEVICE_OBJECT, PIRP);
	NTSTATUS DriverIrpClose(PDEVICE_OBJECT, PIRP);
	NTSTATUS DriverIrpDeviceControl(PDEVICE_OBJECT, PIRP);
	void DriverUnload(PDRIVER_OBJECT DriverObject);
}

namespace Memory 
{

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

    NTSTATUS ReadProcessMemory(
        PIRP Irp,
        P_READ_PACK ReadInfo
    );

    NTSTATUS WriteProcessMemory(
        PIRP Irp,
        P_WRITE_PACK WriteInfo
    );

}