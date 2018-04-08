// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup_Speed.h"
#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
#include "MyPawnMovementComponent.h"

APickup_Speed::APickup_Speed() : APickup()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> 
		StaticMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Bush.SM_Bush'"));
	if (StaticMeshAsset.Succeeded()) {
		MeshComponent->SetWorldScale3D(FVector(0.4f));
		MeshComponent->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void APickup_Speed::OnPlayerPickup(AMyPawn* Player)
{
	Player->GetMyPawnMovementComponent()->IncreaseSpeedMultiplier(0.5f);
	FString pickup = FString::Printf(TEXT("Picked up speed upgrade!"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, pickup);
}
