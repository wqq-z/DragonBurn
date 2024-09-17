#pragma once
#include "KernelApi.h"

// Structure for getting module address base
typedef struct _MODULE_PACK
{
	UINT32 pid;
	UINT64 baseAddress;
	SIZE_T size;
	WCHAR moduleName[256];
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

NTSTATUS ReadProcessMemory(P_READ_PACK);

NTSTATUS WriteProcessMemory(P_WRITE_PACK);

NTSTATUS WriteProcessMemoryProtected(P_WRITE_PACK);// write virtual memory, with less restrictions, should only be used for byte patching in protected memory regions