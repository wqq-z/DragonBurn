#pragma once
#include "KernelApi.h"

NTSTATUS DriverIrpCreate(PDEVICE_OBJECT, PIRP);

NTSTATUS DriverIrpClose(PDEVICE_OBJECT, PIRP);

NTSTATUS DriverIrpDeviceControl(PDEVICE_OBJECT, PIRP);

void DriverUnload(PDRIVER_OBJECT);