// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndScreenWorldManager.generated.h"

UCLASS()
class MYPROJECT5_API AEndScreenWorldManager : public AActor
{
	GENERATED_BODY()

	float ElapsedTime = 0.0f;
public:	
	// Sets default values for this actor's properties
	AEndScreenWorldManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
