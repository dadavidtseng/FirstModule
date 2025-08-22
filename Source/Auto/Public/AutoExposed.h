//----------------------------------------------------------------------------------------------------
// AutoExposed.h
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
#pragma once

#include <CoreMinimal.h>

#include <AutoExposed.generated.h>

//----------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class AUTO_API AAutoExposed : public AActor
{
	GENERATED_BODY()

public:
	AAutoExposed();

	UFUNCTION(BlueprintCallable, Category = "Auto")
	void DoAutoExposed() const;
};
