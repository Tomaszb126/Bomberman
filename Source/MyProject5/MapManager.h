// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapManager.generated.h"

UCLASS()
class MYPROJECT5_API AMapManager : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FVector MapOrigin = FVector(0.0f, 0.0f, 0.0f);
	float TileSize = 100.0f;
	UPROPERTY(EditAnywhere)
	int MapSizeX = 15;
	UPROPERTY(EditAnywhere)
	int MapSizeY = 13;

public:	
	// Sets default values for this actor's properties
	AMapManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
