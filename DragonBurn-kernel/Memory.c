#pragma once
#include "Memory.h"

NTSTATUS ReadProcessMemory(P_READ_PACK ReadPack)
{
	if (!ReadPack)
		return STATUS_INVALID_PARAMETER;

	DbgPrint("[+] ReadProcessMemory called\n");

	PEPROCESS Process;

	// lookup eprocess for use in attaching
	if (!NT_SUCCESS(PsLookupProcessByProcessId((PVOID)ReadPack->pid, &Process)))
		return STATUS_INVALID_PARAMETER_1;

	// create our own variables for usermode buffer, for some reason it will crash if we dont use these variables
	PVOID Address = (PVOID)ReadPack->address;
	SIZE_T Size = ReadPack->size;

	// alocate memory for our driverbuffer, will be used to read memory from the process
	PVOID* Buffer = (PVOID*)ExAllocatePool(NonPagedPool, Size); // Pointer to Allocated Memory
	if (Buffer == NULL) {
		DbgPrint("[-] Failed to alocate memory for our driverbuffer\n");
		ObfDereferenceObject(Process);

		return STATUS_MEMORY_NOT_ALLOCATED;
	}

	RtlSecureZeroMemory(Buffer, Size);

	KAPC_STATE APC;
	NTSTATUS Status = STATUS_FAIL_CHECK;

	__try {
		// attach
		KeStackAttachProcess(Process, &APC);

		// query information on memory to verify it meets our requirements
		MEMORY_BASIC_INFORMATION info;
		if (!NT_SUCCESS(ZwQueryVirtualMemory(ZwCurrentProcess(), Address, MemoryBasicInformation, &info, sizeof(MEMORY_BASIC_INFORMATION), NULL))) {
			DbgPrint("[-] ZwQueryVirtualMemory failed\n");
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_INVALID_ADDRESS_COMPONENT;

			return Status;
		}

		ULONG flags = PAGE_EXECUTE_READWRITE | PAGE_READWRITE | PAGE_EXECUTE_READ;
		ULONG page = PAGE_GUARD | PAGE_NOACCESS;

		// confirm memory block meets our requirements
		if (!(info.State & MEM_COMMIT) || !(info.Protect & flags) || (info.Protect & page)) {
			DbgPrint("[-] Block doesn't meet our requirements\n");
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_DENIED;

			return Status;
		}

		// secure memory so it doesnt change between the beginning of the request & the end, practically the same as doing ZwProtectVirtualMemory
		HANDLE Secure = MmSecureVirtualMemory(Address, Size, PAGE_READWRITE);
		if (Secure == NULL) {
			DbgPrint("[-] Memory is not secured\n");

			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_VIOLATION;

			return Status;
		}

		if (MmIsAddressValid(Address) == FALSE) {
			DbgPrint("[-] Memory is invalid\n");
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_VIOLATION;

			return Status;
		}

		// read memory to our driver's buffer
		memcpy(Buffer, Address, Size);

		// cleanup, unsecure memory & detach from process
		MmUnsecureVirtualMemory(Secure);
		KeUnstackDetachProcess(&APC);

		// read memory from our driver's buffer over to our usermode buffer
		memcpy(ReadPack->buff, Buffer, Size);

		Status = STATUS_SUCCESS;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		// detach if anything goes wrong
		KeUnstackDetachProcess(&APC);
		DbgPrint("[-] Exception occurred\n");
	}

	// cleanup for us, deallocate buffer memory & deref eprocess as we added a ref
	ExFreePool(Buffer);
	ObfDereferenceObject(Process);
	DbgPrint("[+] ReadProcessMemory ended\n");

	return Status;
}

NTSTATUS WriteProcessMemory(P_WRITE_PACK WritePack) 
{
	if (!WritePack)
		return STATUS_INVALID_PARAMETER;

	DbgPrint("[+] WriteProcessMemory called\n");

	PEPROCESS Process;

	// lookup eprocess for use in attaching
	if (!NT_SUCCESS(PsLookupProcessByProcessId((PVOID)WritePack->pid, &Process)))
		return STATUS_INVALID_PARAMETER_1;

	PVOID Address = (PVOID)WritePack->address;
	SIZE_T Size = WritePack->size;

	// allocate memory for our driver buffer
	PVOID* Buffer = (PVOID*)ExAllocatePool(NonPagedPool, Size); // Pointer to Allocated Memory
	if (Buffer == NULL) {
		ObfDereferenceObject(Process);

		return STATUS_MEMORY_NOT_ALLOCATED;
	}

	RtlSecureZeroMemory(Buffer, Size);

	KAPC_STATE APC;
	NTSTATUS Status = STATUS_FAIL_CHECK;

	__try {
		// copy our usermode buffer's value over to our driver's buffer
		memcpy(Buffer, WritePack->buff, Size);

		KeStackAttachProcess(Process, &APC);

		MEMORY_BASIC_INFORMATION info;
		if (!NT_SUCCESS(ZwQueryVirtualMemory(ZwCurrentProcess(), Address, MemoryBasicInformation, &info, sizeof(MEMORY_BASIC_INFORMATION), NULL))) {
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_INVALID_PARAMETER_2;

			return Status;
		}

		ULONG flags = PAGE_EXECUTE_READWRITE | PAGE_READWRITE;
		ULONG page = PAGE_GUARD | PAGE_NOACCESS;

		if (!(info.State & MEM_COMMIT) || !(info.Protect & flags) || (info.Protect & page)) {
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_DENIED;

			return Status;
		}

		HANDLE Secure = MmSecureVirtualMemory(Address, Size, PAGE_READWRITE);
		if (Secure == NULL) {
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_VIOLATION;

			return Status;
		}

		if (MmIsAddressValid(Address) == FALSE) {
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_VIOLATION;

			return Status;
		}

		// send our driver's buffer to our applications memory address
		memcpy(Address, Buffer, Size);

		MmUnsecureVirtualMemory(Secure);
		KeUnstackDetachProcess(&APC);

		Status = STATUS_SUCCESS;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		KeUnstackDetachProcess(&APC);
	}

	ExFreePool(Buffer);
	ObfDereferenceObject(Process);

	DbgPrint("[+] WriteProcessMemory ended\n");
	return Status;
}

NTSTATUS WriteProcessMemoryProtected(P_WRITE_PACK WritePack)// write virtual memory, with less restrictions, should only be used for byte patching in protected memory regions
{
	if (!WritePack)
		return STATUS_INVALID_PARAMETER;

	DbgPrint("[+] WriteProcessMemoryProtected called\n");

	PEPROCESS Process;
	KAPC_STATE APC;
	NTSTATUS Status;

	// lookup eprocess for use in attaching
	if (!NT_SUCCESS(PsLookupProcessByProcessId((PVOID)WritePack->pid, &Process)))
		return STATUS_INVALID_PARAMETER_1;

	PVOID Address = (PVOID)WritePack->address;
	PVOID ProtectedAddress = (PVOID)WritePack->address;
	SIZE_T Size = WritePack->size;
	SIZE_T ProtectedSize = WritePack->size;

	PVOID* Buffer = (PVOID*)ExAllocatePool(NonPagedPool, Size); // Pointer to Allocated Memory
	if (Buffer == NULL) {
		ObfDereferenceObject(Process);

		return STATUS_MEMORY_NOT_ALLOCATED;
	}

	RtlSecureZeroMemory(Buffer, Size);

	__try {
		memcpy(Buffer, WritePack->buff, Size);

		KeStackAttachProcess(Process, &APC);

		ULONG OldProtection;
		Status = ZwProtectVirtualMemory(ZwCurrentProcess(), &ProtectedAddress, &ProtectedSize, PAGE_EXECUTE_READWRITE, &OldProtection);
		if (!NT_SUCCESS(Status)) {
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			return Status;
		}

		ProtectedAddress = Address;
		ProtectedSize = Size;

		MEMORY_BASIC_INFORMATION info;
		Status = ZwQueryVirtualMemory(ZwCurrentProcess(), Address, MemoryBasicInformation, &info, sizeof(MEMORY_BASIC_INFORMATION), NULL);
		if (!NT_SUCCESS(Status)) {
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			return Status;
		}

		if (!(info.State & MEM_COMMIT)) {
			ZwProtectVirtualMemory(ZwCurrentProcess(), &ProtectedAddress, &ProtectedSize, OldProtection, &OldProtection);
			KeUnstackDetachProcess(&APC);

			ExFreePool(Buffer);
			ObfDereferenceObject(Process);

			Status = STATUS_ACCESS_DENIED;

			return Status;
		}

		memcpy(Address, Buffer, Size);

		ZwProtectVirtualMemory(ZwCurrentProcess(), &ProtectedAddress, &ProtectedSize, OldProtection, &OldProtection);
		KeUnstackDetachProcess(&APC);

		Status = STATUS_SUCCESS;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		KeUnstackDetachProcess(&APC);
	}

	ExFreePool(Buffer);
	ObfDereferenceObject(Process);

	DbgPrint("[+] WriteProcessMemoryProtected ended\n");
	return Status;
}