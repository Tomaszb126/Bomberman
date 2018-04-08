// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyPawnMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API UMyPawnMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()

	float SpeedMultiplier = 1.0f;
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, 
		FActorComponentTickFunction *ThisTickFunction) override;
	void IncreaseSpeedMultiplier(float Speed) { SpeedMultiplier += Speed; }

};
