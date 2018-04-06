// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup_Bombs.h"
#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "MyPawnMovementComponent.h"

APickup_Bombs::APickup_Bombs() : APickup() 
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Bush.SM_Bush'"));
	if (StaticMeshAsset.Succeeded()) {
		MeshComponent->SetWorldScale3D(FVector(0.4f));
		MeshComponent->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void APickup_Bombs::OnPlayerPickup(AMyPawn* Player)
{
	Player->IncreaseMaxBombs(1);
	Player->OurMovementComponent->IncreaseSpeedMultiplier(0.5f);
	Player->IncreaseBombBlastDistance(1);
	FString pickup = FString::Printf(TEXT("Picked up upgrade."));
	GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, pickup);

}
