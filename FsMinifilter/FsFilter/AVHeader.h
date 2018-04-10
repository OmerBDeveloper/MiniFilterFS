#pragma once

#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>
#include <ntdef.h>


/*************************************************************************
Prototypes
*************************************************************************/

bool IsThreatByFilename(PUNICODE_STRING fileName);

EXTERN_C_START

DRIVER_INITIALIZE DriverEntry;

NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath);

NTSTATUS FsFilterUnload(_In_ FLT_FILTER_UNLOAD_FLAGS Flags);

FLT_PREOP_CALLBACK_STATUS AntiVirusPreReadOperation(_Inout_ PFLT_CALLBACK_DATA Data,
											   _In_ PCFLT_RELATED_OBJECTS FltObjects,
											   _Flt_CompletionContext_Outptr_ PVOID *CompletionContext);

EXTERN_C_END
