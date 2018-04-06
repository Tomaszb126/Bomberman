// Fill out your copyright notice in the Description page of Project Settings.

#include "EndScreenWorldManager.h"
#include "TimerManager.h"


// Sets default values
AEndScreenWorldManager::AEndScreenWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEndScreenWorldManager::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle Timer;
	//GetWorldTimerManager().SetTimer(Timer, this, &AEndScreenWorldManager::EndGame, 3.1f);
}

// Called every frame
void AEndScreenWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

