// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DestructibleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT5_API AMyPawn : public APawn
{
	GENERATED_BODY()

	int MaxBombs = 1;
	float BombBlastRange = 100.0f;
	class UMyPawnMovementComponent* OurMovementComponent;
	FVector CurrentVelocity;

	UFUNCTION()
	void PlayerGetHit(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMesh;

	UMyPawnMovementComponent* GetMyPawnMovementComponent() const;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PlaceBomb();
	void IncreaseBombBlastRange(float IncreaseBy) { BombBlastRange += IncreaseBy; }
	float GetBombBlastRange() { return BombBlastRange; }
	void IncreaseMaxBombs(int IncreaseBy) { MaxBombs += IncreaseBy; }
	int GetMaxBombs() { return MaxBombs; }
	void QuitGame() { GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit"); }
};
