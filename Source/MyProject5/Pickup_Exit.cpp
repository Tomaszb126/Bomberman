// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup_Exit.h"
#include "Engine.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInterface.h"
#include "MyPawnMovementComponent.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"

APickup_Exit::APickup_Exit() : APickup()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Props/SM_WindowFrame.SM_WindowFrame'"));
	if (StaticMeshAsset.Succeeded()) {
		MeshComponent->SetWorldScale3D(FVector(0.2f));
		MeshComponent->SetStaticMesh(StaticMeshAsset.Object);
		MeshComponent->SetWorldTransform(FTransform(FVector(0.0f, 0.0f, 40.0f)));
		//MeshComponent->SetWorldRotation(FQuat(90.000000f, -179.841736f, -179.841736f, 0.0f));
	}
	Box->SetWorldScale3D(FVector(1.5f, 1.5f, 1.5f));
}

void APickup_Exit::OnPlayerPickup(AMyPawn* Player)
{
	FString pickup = FString::Printf(TEXT("Exit entered"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, pickup);
	UGameplayStatics::OpenLevel(this, "GameEndMap");
}



