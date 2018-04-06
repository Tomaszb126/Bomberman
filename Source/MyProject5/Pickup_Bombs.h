// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Pickup_Bombs.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API APickup_Bombs : public APickup
{
	GENERATED_BODY()
	
public:
	APickup_Bombs();

	void OnPlayerPickup(AMyPawn* Player) override;
	
};
