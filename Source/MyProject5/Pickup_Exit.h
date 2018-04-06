// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Pickup_Exit.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API APickup_Exit : public APickup
{
	GENERATED_BODY()
	
	APickup_Exit();
	void OnPlayerPickup(AMyPawn* Player) override;
};
