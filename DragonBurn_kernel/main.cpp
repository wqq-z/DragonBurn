#include "Kernel.h"

NTSTATUS DriverMain(PDRIVER_OBJECT, PUNICODE_STRING);//ed nt!Kd_IHVDRIVER_Mask 8

//kdmapper calls it with PDRIVER_OBJECT = NONE; PUNICODE_STRING = NONE;
NTSTATUS DriverEntry()//PDRIVER_OBJECT driverObj, PUNICODE_STRING registeryPath
{
	Log::Print("[i]DriverEntry called\n");

	UNICODE_STRING driverName = {};
	RtlInitUnicodeString(&driverName, L"\\Driver\\DragonBurn_kernel");

	return IoCreateDriver(&driverName, &DriverMain);
}

//Actual kernel driver entry
NTSTATUS DriverMain(PDRIVER_OBJECT driverObj, PUNICODE_STRING registeryPath)
{
	UNREFERENCED_PARAMETER(registeryPath);
	NTSTATUS status = STATUS_UNSUCCESSFUL;

	//create a driver device obj
	UNICODE_STRING deviceName = {};
	RtlInitUnicodeString(&deviceName, L"\\Device\\DragonBurn_kernel");

	PDEVICE_OBJECT deviceObj = nullptr;
	status = IoCreateDevice(driverObj, 0, &deviceName, FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &deviceObj);

	if (status != STATUS_SUCCESS)
	{
		Log::Print("[!]Faild to create a driver device\n");
		return status;
	}
	Log::Print("[+]Driver device successfully created\n");

	//create a symbolic link for a driver
	UNICODE_STRING symbolicLink = {};
	RtlInitUnicodeString(&symbolicLink, L"\\??\\DragonBurn_kernel");//DosDevices

	status = IoCreateSymbolicLink(&symbolicLink, &deviceName);

	if (status != STATUS_SUCCESS)
	{
		Log::Print("[!]Faild to establish a driver symbolic link\n");
		return status;
	}
	Log::Print("[+]Driver symbolic link successfully established\n");

	//Allow us to send small amounts of data between usermode and kernelmode
	SetFlag(deviceObj->Flags, DO_BUFFERED_IO);

	driverObj->MajorFunction[IRP_MJ_CREATE] = Kernel::DriverIrpCreate;
	driverObj->MajorFunction[IRP_MJ_CLOSE] = Kernel::DriverIrpClose;
	driverObj->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Kernel::DriverIrpDeviceControl;
	driverObj->DriverUnload = Kernel::DriverUnload;

	ClearFlag(deviceObj->Flags, DO_DEVICE_INITIALIZING);
	Log::Print("[+]Driver initialized successfully\n");

	return status;
}