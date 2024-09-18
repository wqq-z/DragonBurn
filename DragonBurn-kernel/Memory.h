#pragma once
#include "KernelApi.h"

// Structure for getting module address base
typedef struct _MODULE_PACK
{
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

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY64	InLoadOrderLinks;
	LIST_ENTRY64	InMemoryOrderLinks;
	LIST_ENTRY64	InInitializationOrderLinks;
	UINT64			DllBase;
	UINT64			EntryPoint;
	ULONG			SizeOfImage;
	UNICODE_STRING	FullDllName;
	UNICODE_STRING 	BaseDllName;
	ULONG			Flags;
	USHORT			LoadCount;
	USHORT			TlsIndex;
	PVOID			SectionPointer;
	ULONG			CheckSum;
	PVOID			LoadedImports;
	PVOID			EntryPointActivationContext;
	PVOID			PatchInformation;
	LIST_ENTRY64	ForwarderLinks;
	LIST_ENTRY64	ServiceTagLinks;
	LIST_ENTRY64	StaticLinks;
	PVOID			ContextInformation;
	ULONG64			OriginalBase;
	LARGE_INTEGER	LoadTime;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef unsigned long long QWORD;
typedef unsigned short WORD;
typedef unsigned long DWORD, * PDWORD, * LPDWORD;

NTSTATUS GetModuleBase(P_MODULE_PACK);

NTSTATUS ReadProcessMemory(P_READ_PACK);

NTSTATUS WriteProcessMemory(P_WRITE_PACK);

NTSTATUS WriteProcessMemoryProtected(P_WRITE_PACK);// write virtual memory, with less restrictions, should only be used for byte patching in protected memory regions
