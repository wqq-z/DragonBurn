#include "Kernel.h"

NTSTATUS Kernel::DriverIrpCreate(PDEVICE_OBJECT deviceObj, PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObj);

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

NTSTATUS Kernel::DriverIrpClose(PDEVICE_OBJECT deviceObj, PIRP irp)
{
	UNREFERENCED_PARAMETER(deviceObj);

	IoCompleteRequest(irp, IO_NO_INCREMENT);
	return irp->IoStatus.Status;
}

void Kernel::DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\DragonBurn_kernel");

	IoDeleteSymbolicLink(&symLink);
	IoDeleteDevice(DriverObject->DeviceObject);

	Log::Print("[+] DragonBurn driver unloaded\n");
}

NTSTATUS Kernel::DriverIrpDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp) {
    UNREFERENCED_PARAMETER(DeviceObject);

    NTSTATUS ntResult = STATUS_SUCCESS;
    PIO_STACK_LOCATION Stack = IoGetCurrentIrpStackLocation(Irp);

    switch (Stack->Parameters.DeviceIoControl.IoControlCode)
    {

    case IOCTL_READ_PROCESS_MEMORY:
    {
        if (Stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(Memory::READ_PACK)) 
        {
            ntResult = STATUS_BUFFER_TOO_SMALL;
            break;
        }
        ntResult = Memory::ReadProcessMemory(Irp, (Memory::P_READ_PACK)Stack->Parameters.DeviceIoControl.Type3InputBuffer);
        break;
    }

    case IOCTL_WRITE_PROCESS_MEMORY:
    {
        if (Stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(Memory::WRITE_PACK)) 
        {
            ntResult = STATUS_BUFFER_TOO_SMALL;
            break;
        }
        ntResult = Memory::WriteProcessMemory(Irp, (Memory::P_WRITE_PACK)Stack->Parameters.DeviceIoControl.Type3InputBuffer);
        break;
    }

    default:
    {
        ntResult = STATUS_INVALID_DEVICE_REQUEST;
        break;
    }

    }

    Irp->IoStatus.Status = ntResult;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return ntResult;
}