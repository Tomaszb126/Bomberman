// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleWall.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ADestructibleWall::ADestructibleWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DESTRUCTIBLE_WALL"));
	RootComponent = StaticMesh;

	//Mesh
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	if(StaticMeshAsset.Succeeded()) StaticMesh->SetStaticMesh(StaticMeshAsset.Object);

	//Material
	ConstructorHelpers::FObjectFinder<UMaterial> StaticMeshMaterial(TEXT("Material'/Game/StarterContent/Materials/M_CobbleStone_Smooth.M_CobbleStone_Smooth'"));
	if (StaticMeshMaterial.Succeeded()) {
		auto* MaterialInstance = UMaterialInstanceDynamic::Create(StaticMeshMaterial.Object, StaticMeshMaterial.Object);
		StaticMesh->SetMaterial(0, MaterialInstance);
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

