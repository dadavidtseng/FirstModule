// Fill out your copyright notice in the Description page of Project Settings.


#include "MigrateActor.h"


// Sets default values
AMigrateActor::AMigrateActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UE_LOG(LogTemp, Warning, TEXT("MigrateActor::AMigrateActor"));
}

// Called when the game starts or when spawned
void AMigrateActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMigrateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
