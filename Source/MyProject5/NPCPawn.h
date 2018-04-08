// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "MyPawnMovementComponent.h"
#include "NPCPawn.generated.h"
UCLASS()
class MYPROJECT5_API ANPCPawn : public APawn
{
	GENERATED_BODY()

	UFUNCTION()
	void NPCHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnNPCDestroy(const FVector& HitPoint, const FVector& HitDirection);

	USphereComponent* ColliderSphere;
	bool Fractured = false;
	float ElapsedTime = 0.0f;

public:
	// Sets default values for this pawn's properties
	ANPCPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class UMyPawnMovementComponent* NPCMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;
};
