//----------------------------------------------------------------------------------------------------
// ManualExposed.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>

#include "AutoCppOnly.h"

#include <ManualExposed.generated.h>

//----------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class MANUAL_API AManualExposed : public AActor
{
	GENERATED_BODY()

public:
	AManualExposed();

	UFUNCTION(BlueprintCallable, Category = "Manual")
	void DoManualExposed() const;

	FAutoCppOnly AutoCppOnly;
};
