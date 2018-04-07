// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "Pickup_BlastRange.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT5_API APickup_BlastRange : public APickup
{
	GENERATED_BODY()
	
public:
	APickup_BlastRange();

	void OnPlayerPickup(AMyPawn* Player) override;
	
	
};
