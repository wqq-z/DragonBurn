#include "kernel.h"

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

    SIZE_T bytesRead = 0;
    ntResult = MmCopyVirtualMemory(
        TargetProcess,
        ReadInfo->AddressToRead,
        RequestingProcess,
        ReadInfo->Buffer,
        ReadInfo->NumberOfBytesToRead,
        KernelMode,
        &bytesRead
    );
    //status = MmCopyVirtualMemory(targetProcess, package->address,
    //    PsGetCurrentProcess(), package->buff,
    //    package->size, KernelMode, &package->callback_size);

    if (!NT_SUCCESS(ntResult)) {
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

    SIZE_T bytesWritten = 0;
    ntResult = MmCopyVirtualMemory(
        RequestingProcess,
        WriteInfo->Buffer,
        TargetProcess,
        WriteInfo->AddressToWrite,
        WriteInfo->NumberOfBytesToWrite,
        KernelMode,
        &bytesWritten
    );

    if (!NT_SUCCESS(ntResult)) {
        Log::Print("[-] Failed to copy user buffer into process memory\n");
    }

    ObDereferenceObject(TargetProcess);
    return ntResult;
}
