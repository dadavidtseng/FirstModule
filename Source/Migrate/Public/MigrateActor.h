// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MigrateActor.generated.h"

UCLASS()
class MIGRATE_API AMigrateActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMigrateActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
