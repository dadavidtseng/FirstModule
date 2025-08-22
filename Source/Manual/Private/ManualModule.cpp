//----------------------------------------------------------------------------------------------------
// ManualModule.cpp
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#include "ManualModule.h"

#include <Modules/ModuleManager.h>

//----------------------------------------------------------------------------------------------------
DEFINE_LOG_CATEGORY(LogManual);

#define LOCTEXT_NAMESPACE "FManualModule"

//----------------------------------------------------------------------------------------------------
void FManualModule::StartupModule()
{
    UE_LOG(LogManual, Warning, TEXT("FManualModule::StartupModule()"));
}

//----------------------------------------------------------------------------------------------------
void FManualModule::ShutdownModule()
{
    UE_LOG(LogManual, Warning, TEXT("FManualModule::ShutdownModule()"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FManualModule, Manual)