// Fill out your copyright notice in the Description page of Project Settings.

#include "IndestructibleWall.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

// Sets default values
AIndestructibleWall::AIndestructibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall"));
	RootComponent = StaticMesh;

	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if (StaticMeshAsset.Succeeded()) StaticMesh->SetStaticMesh(StaticMeshAsset.Object);

	ConstructorHelpers::FObjectFinder<UMaterialInterface> StaticMeshMaterialAsset(TEXT("Material'/Game/StarterContent/Materials/M_Brick_Clay_New.M_Brick_Clay_New'"));
	if (StaticMeshMaterialAsset.Succeeded()) StaticMesh->SetMaterial(0, StaticMeshMaterialAsset.Object);
}

// Called when the game starts or when spawned
void AIndestructibleWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIndestructibleWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

