// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Pickup_Speed.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API APickup_Speed : public APickup
{
	GENERATED_BODY()
	
public:
	APickup_Speed();

	void OnPlayerPickup(AMyPawn* Player) override;
	
};
