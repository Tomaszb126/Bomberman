// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DestructibleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleWall.generated.h"

UCLASS()
class MYPROJECT5_API ADestructibleWall : public AActor
{
	GENERATED_BODY()


	bool Fractured = false;
	UDestructibleComponent* DestructibleComponent;

public:	
	// Sets default values for this actor's properties
	ADestructibleWall();

	UFUNCTION()
	void SpawnPickup(const FVector& HitPoint, const FVector& HitDirection);
	UFUNCTION()
	void SpawnExit(const FVector& HitPoint, const FVector& HitDirection);

	UDestructibleComponent *GetDestructibleComponent() const { return DestructibleComponent; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
