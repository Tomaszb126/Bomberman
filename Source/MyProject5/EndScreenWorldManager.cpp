// Fill out your copyright notice in the Description page of Project Settings.

#include "EndScreenWorldManager.h"
#include "TimerManager.h"
#include "Classes/AIController.h"
#include "NPCPawn.h"
#include "Engine/World.h"


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
}

// Called every frame
void AEndScreenWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 2.5f) GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

