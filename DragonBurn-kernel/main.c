//special thank to lennyRBLX
#include "Kernel.h"

NTSTATUS DriverMain(PDRIVER_OBJECT, PUNICODE_STRING);

//kdmapper calls it with PDRIVER_OBJECT = NONE; PUNICODE_STRING = NONE;
NTSTATUS DriverEntry()
{
	DbgPrint("[+] DriverEntry called\n");//ed nt!Kd_Default_Mask 8

	UNICODE_STRING driverName;
	RtlInitUnicodeString(&driverName, L"\\Driver\\DragonBurn-kernel");

	return IoCreateDriver(&driverName, &DriverMain);
}

NTSTATUS DriverMain(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	DbgPrint("[+] DriverMain called\n");

	//create a driver device obj
	UNICODE_STRING deviceName;
	RtlInitUnicodeString(&deviceName, L"\\Device\\DragonBurn-kernel");

	PDEVICE_OBJECT deviceObj;
	status = IoCreateDevice(DriverObject, 0, &deviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObj);//FILE_DEVICE_SECURE_OPEN -> NULL
	if (status != STATUS_SUCCESS)
	{
		DbgPrint("[-] Failed to create device\n");//0x%08x
		return status;
	}

	//create a symbolic link for a driver
	UNICODE_STRING symbolicLink;
	RtlInitUnicodeString(&symbolicLink, L"\\??\\DragonBurn-kernel");//DosDevices

	status = IoCreateSymbolicLink(&symbolicLink, &deviceName);
	if (status != STATUS_SUCCESS)
	{
		DbgPrint("[-] Failed to create symbolic link\n");
		return status;
	}

	//Allow us to send small amounts of data between usermode and kernelmode
	SetFlag(deviceObj->Flags, DO_BUFFERED_IO);

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DriverIrpCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverIrpClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DriverIrpDeviceControl;
	DriverObject->DriverUnload = DriverUnload;

	ClearFlag(deviceObj->Flags, DO_DEVICE_INITIALIZING);

	DbgPrint("[+] Drivel loaded\n");

	return status;
}