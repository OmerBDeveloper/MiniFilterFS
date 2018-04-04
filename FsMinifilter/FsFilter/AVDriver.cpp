#include "AVHeader.h"

#define THREAT_REGEX L"*VIRUS*"

UNICODE_STRING threatRegex = RTL_CONSTANT_STRING(THREAT_REGEX);



bool isMaliciousFileName(PUNICODE_STRING fileName)
{
	bool isThreat = FsRtlIsNameInExpression(&threatRegex,
		fileName,
		TRUE,
		NULL);
	return true;
}

FLT_PREOP_CALLBACK_STATUS
FsFilterPreOperation(
	_Inout_ PFLT_CALLBACK_DATA Data,
	_In_ PCFLT_RELATED_OBJECTS FltObjects,
	_Flt_CompletionContext_Outptr_ PVOID *CompletionContext
)
{
	UNREFERENCED_PARAMETER(CompletionContext);
	PUNICODE_STRING fileName = &FltObjects->FileObject->FileName;

	bool isThreat = isMaliciousFileName(fileName);

	if (isThreat)
	{
		DbgPrint("OHH NOOOOOOO VIRUS ALeRTTTTTTTTT");
		FltCancelFileOpen(FltObjects->Instance, FltObjects->FileObject);
		Data->IoStatus.Status = STATUS_VIRUS_INFECTED;
		Data->IoStatus.Information = 0;
		return FLT_PREOP_COMPLETE;
		
	}
	else
	{
		Data->IoStatus.Status = STATUS_SUCCESS;
		Data->IoStatus.Information = 0;
		return FLT_PREOP_SUCCESS_NO_CALLBACK;
	}
}