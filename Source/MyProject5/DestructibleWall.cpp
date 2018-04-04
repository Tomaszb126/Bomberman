// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleWall.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"

// Sets default values
ADestructibleWall::ADestructibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UDestructibleComponent* DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("DESTRUCTIBLE_WALL"));
	RootComponent = DestructibleComponent;

	//Mesh
	ConstructorHelpers::FObjectFinder<UDestructibleMesh> DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Cube_Brick_DM.Shape_Cube_Brick_DM'"));
	if (DestructibleMeshAsset.Succeeded()) DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);
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

