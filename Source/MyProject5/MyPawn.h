// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT5_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UParticleSystemComponent* OurParticleSystem;
	class UMyPawnMovementComponent* OurMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	float GetSpeedMultiplier() { return Speed; }

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PlaceBomb();
	void CauseExplosion();

	int MaxBombs = 2;
	float Speed = 1.0f;

	FVector CurrentVelocity;
	
};
