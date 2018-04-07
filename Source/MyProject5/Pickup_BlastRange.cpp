// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup_BlastRange.h"
#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"

APickup_BlastRange::APickup_BlastRange() : APickup()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	if (StaticMeshAsset.Succeeded()) {
		MeshComponent->SetWorldScale3D(FVector(0.2f));
		MeshComponent->SetStaticMesh(StaticMeshAsset.Object);
	}
}

void APickup_BlastRange::OnPlayerPickup(AMyPawn* Player)
{
	Player->IncreaseBombBlastRange(100.0f);
	FString pickup = FString::Printf(TEXT("Picked up bomb upgrade! Blast range: %f"), Player->GetBombBlastRange()/100);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, pickup);
}


