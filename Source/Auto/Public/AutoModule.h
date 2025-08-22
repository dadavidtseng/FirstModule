//----------------------------------------------------------------------------------------------------
// AutoModule.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

//----------------------------------------------------------------------------------------------------
DECLARE_LOG_CATEGORY_EXTERN(LogAuto, Log, All);

class FAutoModule final : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
