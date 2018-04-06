// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"
#include "DestructibleWall.h"
#include "IndestructibleWall.h"
#include "MyPawn.h"
#include "Engine/World.h"


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
				int ShouldSpawn = FMath::RandRange(0, 1);
				if(ShouldSpawn)
					GetWorld()->SpawnActor<ADestructibleWall>(Position, Rotation, SpawnInfo);
			}
		}
}

// Called every frame
void AMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

