// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleWall.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "Engine/World.h"
#include "Pickup_Bombs.h"
#include "Pickup_Speed.h"
#include "Pickup_Exit.h"
#include "Pickup_BlastRange.h"

// Sets default values
ADestructibleWall::ADestructibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create destructible component for root
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DESTRUCTIBLE_WALL"));
	RootComponent = DestructibleComponent;
	//DestructibleComponent->OnComponentFracture.AddDynamic(this, &ADestructibleWall::SpawnPickup);

	//Mesh
	ConstructorHelpers::FObjectFinder<UDestructibleMesh> 
		DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Cube_Brick_DM.Shape_Cube_Brick_DM'"));
	if (DestructibleMeshAsset.Succeeded()) {
		DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);
		DestructibleComponent->SetWorldScale3D(FVector(0.9f));
	}
}

// Called when the game starts or when spawned
void ADestructibleWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestructibleWall::SpawnPickup(const FVector& HitPoint, const FVector& HitDirection)
{
	if (!Fractured) {
		Fractured = true;
		UE_LOG(LogTemp, Warning, TEXT("Wall destroyed, spawn pickup"));

		FVector Position = FVector(0.0f, 0.0f, 20.0f) + GetActorLocation();
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		int ShouldSpawn = FMath::RandRange(1, 100);
		if (ShouldSpawn < 85) return ;
		else if (ShouldSpawn >= 85 && ShouldSpawn <= 90)
			GetWorld()->SpawnActor<APickup_BlastRange>(Position, Rotation, SpawnInfo);
		else if (ShouldSpawn >= 90 && ShouldSpawn <=95)
			GetWorld()->SpawnActor<APickup_Bombs>(Position, Rotation, SpawnInfo);
		else if (ShouldSpawn >= 95 && ShouldSpawn <= 100)
			GetWorld()->SpawnActor<APickup_Speed>(Position, Rotation, SpawnInfo);
	}
}

void ADestructibleWall::SpawnExit(const FVector & HitPoint, const FVector & HitDirection)
{
	if (!Fractured) {
		Fractured = true;
		UE_LOG(LogTemp, Warning, TEXT("Wall destroyed, spawn exit"));

		FVector Position = FVector(0.0f, 0.0f, 0.0f) + GetActorLocation();
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		GetWorld()->SpawnActor<APickup_Exit>(Position, Rotation, SpawnInfo);
	}
}

