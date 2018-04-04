// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh"));

	//ConstructorHelpers::FObjectFinder<UStaticMesh> BombMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	//mesh->SetStaticMesh(BombMesh.Object);


	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("BOMB"));
	RootComponent = DestructibleComponent;

	//Mesh
	ConstructorHelpers::FObjectFinder<UDestructibleMesh> DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Sphere_Bomb_DM.Shape_Sphere_Bomb_DM'"));
	if (DestructibleMeshAsset.Succeeded()) DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);

	//SetLifeSpan(3.0f);

	RootComponent = mesh;

	//this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &ABomb::BombExplode, Lifetime);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABomb::BombExplode()
{
	// Create explosion
	UE_LOG(LogTemp, Warning, TEXT("Granat dsadbum"));
	DestructibleComponent->ApplyDamage(100.0f, GetActorLocation(), FVector(0.0f, 0.0f, -1.0f), 1.0f);
	//this->Destroy();
}

