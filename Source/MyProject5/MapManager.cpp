// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"
#include "DestructibleWall.h"
#include "IndestructibleWall.h"
#include "MyPawn.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "Classes/AIController.h"
#include "NPCPawn.h"
#include "Engine.h"


// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMapManager::BeginPlay()
{
	Super::BeginPlay();

	//Create map
	for(int x = 0; x < MapSizeX; x++)
		for (int y = 0; y < MapSizeY; y++)
		{
			if ((x == 1 && y == 2) || x == 2 && y == 1)
				continue;
			
			FVector Position = FVector(y*TileSize, x*TileSize, 0.0f) + MapOrigin;
			FRotator Rotation(0.0f, 0.0f, 0.0f);
			FActorSpawnParameters SpawnInfo;

			if ((x == 1 && y == 1))
				GetWorld()->SpawnActor<AMyPawn>(Position, Rotation, SpawnInfo);
			else if (x == 0 || y == 0 || x == MapSizeX - 1 || y == MapSizeY - 1 || (x % 2 == 0 && y % 2 == 0))
				GetWorld()->SpawnActor<AIndestructibleWall>(Position, Rotation, SpawnInfo);
			else {
				int ShouldSpawn = FMath::RandRange(0, 100);
				if (ShouldSpawn >= 50)
					GetWorld()->SpawnActor<ADestructibleWall>(Position, Rotation, SpawnInfo);
				else if (ShouldSpawn >= 40 && ShouldSpawn < 50) {
					if ((x == 3 && y == 1) || (y == 3 && x == 1))
						continue; // dont want to spawn npc so close to the player
					GetWorld()->SpawnActor<ANPCPawn>(Position, Rotation, SpawnInfo);
				}
			}
		}

	TArray<AActor*> DestructibleWalls;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADestructibleWall::StaticClass(), DestructibleWalls);
	int DestructibleWallCount = DestructibleWalls.Num();
	int ExitIndex = FMath::RandRange(0, DestructibleWallCount - 1);
	//int ExitIndex = 1;
	UE_LOG(LogTemp, Warning, TEXT("DesWall count: %d ExitWallIndex: %d"), DestructibleWallCount, ExitIndex);

	for (int i = 0; i < DestructibleWallCount; i++)
	{
		ADestructibleWall* DestructableWall = Cast<ADestructibleWall>(DestructibleWalls[i]);
		if (i != ExitIndex)
		{
			DestructableWall->GetDestructibleComponent()->OnComponentFracture
				.AddDynamic(DestructableWall, &ADestructibleWall::SpawnPickup);
		}
		else
		{
			DestructableWall->GetDestructibleComponent()->OnComponentFracture
				.AddDynamic(DestructableWall, &ADestructibleWall::SpawnExit);
		}
	}

	// Instructions
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("W,S,A,D - movement")));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Spacebar - place bomb")));
}

// Called every frame
void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

