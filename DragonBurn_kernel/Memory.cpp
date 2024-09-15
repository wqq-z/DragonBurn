#include "Kernel.h"
#define PAGE_READABLE (PAGE_READONLY | PAGE_READWRITE | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE)
#define PAGE_WRITABLE (PAGE_READWRITE | PAGE_EXECUTE_READWRITE)

NTSTATUS Memory::ReadProcessMemory(
    PIRP Irp,
    P_READ_PACK ReadInfo
) {
    if (!ReadInfo || !Irp) {
        return STATUS_INVALID_PARAMETER;
    }

    PEPROCESS TargetProcess = nullptr;
    PEPROCESS RequestingProcess = IoGetRequestorProcess(Irp);//PsGetCurrentProcess()
    if (!RequestingProcess) {
        Log::Print("[-] Failed to find requesting process\n");
        return STATUS_ACCESS_DENIED;
    }

    NTSTATUS ntResult = PsLookupProcessByProcessId(reinterpret_cast<HANDLE>(ReadInfo->ProcessId), &TargetProcess);
    if (!NT_SUCCESS(ntResult)) {
        Log::Print("[-] Failed to find process with PID\n");
        return ntResult;
    }

    Log::Print("[+] Process requested to read bytes from process at address\n");

    if (!MmIsAddressValid(ReadInfo->AddressToRead) || !MmIsAddressValid(ReadInfo->Buffer)) 
    {
        Log::Print("[-] Invalid memory address encountered\n");
        ObDereferenceObject(TargetProcess);
        return STATUS_ACCESS_VIOLATION;
    }

    MEMORY_BASIC_INFORMATION mbi;
    NTSTATUS ntStatus = ZwQueryVirtualMemory(
        TargetProcess,
        ReadInfo->AddressToRead,
        MemoryBasicInformation,
        &mbi,
        sizeof(mbi),
        NULL
    );

    if (!NT_SUCCESS(ntStatus) || !(mbi.Protect & PAGE_READABLE))
    {
        Log::Print("[-] Memory is not readable or invalid\n");
        ObDereferenceObject(TargetProcess);
        return STATUS_ACCESS_VIOLATION;
    }

    __try 
    {
        ProbeForRead(ReadInfo->Buffer, ReadInfo->NumberOfBytesToRead, sizeof(UCHAR));
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::Print("[-] Buffer is not valid for read access\n");
        ObDereferenceObject(TargetProcess);
        return STATUS_ACCESS_VIOLATION;
    }

    SIZE_T bytesRead = 0;
    __try 
    {
        ntResult = MmCopyVirtualMemory(
            TargetProcess,
            ReadInfo->AddressToRead,
            RequestingProcess,
            ReadInfo->Buffer,
            ReadInfo->NumberOfBytesToRead,
            KernelMode,
            &bytesRead
        );
        Log::Print("[+] Memory read!!!\n");
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        Log::Print("[-] Exception occurred during MmCopyVirtualMemory\n");
        ntResult = GetExceptionCode();
    }

    if (!NT_SUCCESS(ntResult))
    {
        Log::Print("[-] Failed to copy process memory into user buffer\n");
    }

    ObDereferenceObject(TargetProcess);
    return ntResult;
}

NTSTATUS Memory::WriteProcessMemory(
    PIRP Irp,
    P_WRITE_PACK WriteInfo
) {
    if (!WriteInfo || !Irp) {
        return STATUS_INVALID_PARAMETER;
    }

    PEPROCESS TargetProcess = nullptr;
    PEPROCESS RequestingProcess = IoGetRequestorProcess(Irp);
    if (!RequestingProcess) {
        Log::Print("[-] Failed to find requesting process\n");
        return STATUS_ACCESS_DENIED;
    }

    NTSTATUS ntResult = PsLookupProcessByProcessId(reinterpret_cast<HANDLE>(WriteInfo->ProcessId), &TargetProcess);
    if (!NT_SUCCESS(ntResult)) {
        Log::Print("[-] Failed to find process with PID\n");
        return ntResult;
    }

    Log::Print("[+] Process requested to write bytes to process at address\n");

    // Query the target memory region to ensure it's writable
    MEMORY_BASIC_INFORMATION mbi;
    ntResult = ZwQueryVirtualMemory(
        TargetProcess,
        WriteInfo->AddressToWrite,
        MemoryBasicInformation,
        &mbi,
        sizeof(mbi),
        NULL
    );

    if (!NT_SUCCESS(ntResult)) {
        Log::Print("[-] Failed to query memory information\n");
        ObDereferenceObject(TargetProcess);
        return ntResult;
    }

    // Check if the memory is writable using the PAGE_WRITABLE macro
    if (!(mbi.Protect & PAGE_WRITABLE)) {
        Log::Print("[-] Memory is not writable\n");
        ObDereferenceObject(TargetProcess);
        return STATUS_ACCESS_VIOLATION;
    }

    // Validate that the source buffer in the requesting process is safe for reading
    __try {
        ProbeForRead(WriteInfo->Buffer, WriteInfo->NumberOfBytesToWrite, sizeof(UCHAR));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        Log::Print("[-] Source buffer is not valid for read access\n");
        ObDereferenceObject(TargetProcess);
        return STATUS_ACCESS_VIOLATION;
    }

    // Validate that the destination buffer in the target process is safe for writing
    __try {
        ProbeForWrite(WriteInfo->AddressToWrite, WriteInfo->NumberOfBytesToWrite, sizeof(UCHAR));
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        Log::Print("[-] Destination buffer is not valid for write access\n");
        ObDereferenceObject(TargetProcess);
        return STATUS_ACCESS_VIOLATION;
    }

    SIZE_T bytesWritten = 0;

    // Structured Exception Handling (SEH) to prevent BSOD on memory access violation
    __try {
        ntResult = MmCopyVirtualMemory(
            RequestingProcess,
            WriteInfo->Buffer,
            TargetProcess,
            WriteInfo->AddressToWrite,
            WriteInfo->NumberOfBytesToWrite,
            KernelMode,
            &bytesWritten
        );
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        Log::Print("[-] Exception occurred during MmCopyVirtualMemory\n");
        ntResult = GetExceptionCode();
    }

    if (!NT_SUCCESS(ntResult)) {
        Log::Print("[-] Failed to copy user buffer into process memory\n");
    }

    ObDereferenceObject(TargetProcess);
    return ntResult;
}
