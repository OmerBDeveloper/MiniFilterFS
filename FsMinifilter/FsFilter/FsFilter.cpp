/*++
	
	This is the main module of the FsFilter miniFilter driver which runs in Kernel mode

--*/

#include "AVHeader.h"

/// This is the global point to out mini filter instance
PFLT_FILTER gFilterHandle;

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, FsFilterUnload)
#endif

//
//  operation registration
//

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {

	{ IRP_MJ_CREATE,
	  0,
	  AntiVirusPreReadOperation,
	  NULL },

	{ IRP_MJ_OPERATION_END }
};

//
//  This defines what we want to filter with FltMgr
//

CONST FLT_REGISTRATION FilterRegistration = {

	sizeof( FLT_REGISTRATION ),         //  Size
	FLT_REGISTRATION_VERSION,           //  Version
	0,                                  //  Flags
	NULL,                               //  Context
	Callbacks,                          //  Operation callbacks
	FsFilterUnload,                     //  MiniFilterUnload
	NULL,								//  InstanceSetup
	NULL,								//  InstanceQueryTeardown
	NULL,								//  InstanceTeardownStart
	NULL,								//  InstanceTeardownComplete
	NULL,                               //  GenerateFileName
	NULL,                               //  GenerateDestinationFileName
	NULL                                //  NormalizeNameComponent
};



/*************************************************************************
	MiniFilter initialization and unload routines.
*************************************************************************/


/*++

Routine Description:

This is the initialization routine for this miniFilter driver.  This
registers with FltMgr and initializes all global data structures.

Arguments:

DriverObject - Pointer to driver object created by the system to
represent this driver.

RegistryPath - Unicode string identifying where the parameters for this
driver are located in the registry.

Return Value:

Routine can return non success error codes.

--*/

NTSTATUS DriverEntry (_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
	
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS status;

	//  Register with FltMgr to tell it our callback routines
	status = FltRegisterFilter(DriverObject, &FilterRegistration, &gFilterHandle);

	if (NT_SUCCESS(status)) {

		// Start filtering i/o
		status = FltStartFiltering(gFilterHandle);

		/************************************************************************/
		/* STEP 1:																*
		/*		Add a debug print with your name using DbgPrint function.		*
		/*		Compile and test the driver.									*
		/*																		*
		/************************************************************************/

		// ENTER CODE HERE

		if (!NT_SUCCESS( status )) {
			FltUnregisterFilter( gFilterHandle );
		}

		/************************************************************************/
		/* STEP 4:																*
		/*		Monitor registry operations and make sure that no value is		*
		/*		to "virus".														*
		/*		In order to monitor registry operations read about				*
		/*		CmRegisterCallback												*
		/************************************************************************/

		// ENTER CODE HERE

	}

	return status;
}

/*++

Routine Description:

This is the unload routine for this miniFilter driver. This is called
when the minifilter is about to be unloaded. We can fail this unload
request if this is not a mandatory unload indicated by the Flags
parameter.

Arguments:

Flags - Indicating if this is a mandatory unload.

Return Value:

Returns STATUS_SUCCESS.

--*/
NTSTATUS FsFilterUnload (_In_ FLT_FILTER_UNLOAD_FLAGS Flags) {
	
	UNREFERENCED_PARAMETER( Flags );
	PAGED_CODE();

	FltUnregisterFilter( gFilterHandle );

	return STATUS_SUCCESS;
}

