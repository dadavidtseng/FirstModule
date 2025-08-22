//----------------------------------------------------------------------------------------------------
// ManualExposed.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "ManualExposed.h"

#include "ManualModule.h"

//----------------------------------------------------------------------------------------------------
AManualExposed::AManualExposed()
{
	UE_LOG(LogManual, Warning, TEXT("AManualExposed::AManualExposed()"));
}

//----------------------------------------------------------------------------------------------------
void AManualExposed::DoManualExposed() const
{
	UE_LOG(LogManual, Warning, TEXT("AManualExposed::DoManualExposed()"));
	AutoCppOnly.DoAutoCppOnly();
}
