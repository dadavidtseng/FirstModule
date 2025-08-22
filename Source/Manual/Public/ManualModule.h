//----------------------------------------------------------------------------------------------------
// ManualModule.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

//----------------------------------------------------------------------------------------------------
DECLARE_LOG_CATEGORY_EXTERN(LogManual, Log, All);

//----------------------------------------------------------------------------------------------------
class MANUAL_API FManualModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
