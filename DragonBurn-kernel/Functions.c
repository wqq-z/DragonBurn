#include "Kernel.h"
#include "Memory.h"
#include "IOCTL.h"

NTSTATUS DriverIrpCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS DriverIrpClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS DriverIrpDeviceControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	NTSTATUS ntResult = 0;
	PIO_STACK_LOCATION Stack = IoGetCurrentIrpStackLocation(Irp);

	//Execute IOCTL handler
	switch (Stack->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_GET_MODULE_BASE:
		if (Stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(MODULE_PACK))
		{
			ntResult = STATUS_BUFFER_TOO_SMALL;
			break;
		}

		ntResult = GetModuleBase((P_MODULE_PACK)Stack->Parameters.DeviceIoControl.Type3InputBuffer);
		break;

	case IOCTL_READ_PROCESS_MEMORY:
		if (Stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(READ_PACK))
		{
			ntResult = STATUS_BUFFER_TOO_SMALL;
			break;
		}

		ntResult = ReadProcessMemory((P_READ_PACK)Stack->Parameters.DeviceIoControl.Type3InputBuffer);
		break;

	case IOCTL_WRITE_PROCESS_MEMORY:
		if (Stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(WRITE_PACK))
		{
			ntResult = STATUS_BUFFER_TOO_SMALL;
			break;
		}

		ntResult = WriteProcessMemory((P_WRITE_PACK)Stack->Parameters.DeviceIoControl.Type3InputBuffer);
		break;

	case IOCTL_WRITE_PROCESS_MEMORY_PROTECTED:
		if (Stack->Parameters.DeviceIoControl.InputBufferLength < sizeof(WRITE_PACK))
		{
			ntResult = STATUS_BUFFER_TOO_SMALL;
			break;
		}

		ntResult = WriteProcessMemoryProtected((P_WRITE_PACK)Stack->Parameters.DeviceIoControl.Type3InputBuffer);
		break;

	default:
		ntResult = STATUS_INVALID_DEVICE_REQUEST;
		break;

	}

	//Finish the I/O request with the final result of the IOCTL
	Irp->IoStatus.Status = ntResult;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return ntResult;
}

void DriverUnload(PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING symLink = RTL_CONSTANT_STRING(L"\\??\\DragonBurn-kernel");
	IoDeleteSymbolicLink(&symLink);
	IoDeleteDevice(DriverObject->DeviceObject);

	DbgPrint("[+] ReadWriteMemoryDriver unloaded\n");
}