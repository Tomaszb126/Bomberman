// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IndestructibleWall.generated.h"

UCLASS()
class MYPROJECT5_API AIndestructibleWall : public AActor
{
	GENERATED_BODY()

	UStaticMeshComponent* StaticMesh;
	
public:	
	// Sets default values for this actor's properties
	AIndestructibleWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
