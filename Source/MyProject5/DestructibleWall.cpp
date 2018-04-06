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

// Sets default values
ADestructibleWall::ADestructibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DESTRUCTIBLE_WALL"));
	RootComponent = DestructibleComponent;
	DestructibleComponent->OnComponentFracture.AddDynamic(this, &ADestructibleWall::SpawnPickup);
	//DestructibleComponent->OnComponentDeactivated.AddDynamic(this, &ADestructibleWall::SpawnPickup);
	//Box->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPickup);

	//Mesh
	ConstructorHelpers::FObjectFinder<UDestructibleMesh> DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Cube_Brick_DM.Shape_Cube_Brick_DM'"));
	if (DestructibleMeshAsset.Succeeded()) DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);

	DestructibleComponent->SetWorldScale3D(FVector(1.0f));
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

		FVector Position = FVector(0.0f, 0.0f, 10.0f) + GetActorLocation();
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnInfo;
		int ShouldSpawn = FMath::RandRange(0, 100);
		if (ShouldSpawn > 80)
			GetWorld()->SpawnActor<APickup_Bombs>(Position, Rotation, SpawnInfo);
	}
}

