#pragma once
#include "Kernel.h"

namespace Log
{
	inline void Print(PCSTR line)
	{
#ifndef DEBUG
		UNREFERENCED_PARAMETER(line);
#endif

		KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, line));
	}
}