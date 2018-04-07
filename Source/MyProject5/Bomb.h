// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DestructibleComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class MYPROJECT5_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* mesh;

	int BlastDistance = 100.0f;
	int Lifetime = 3;
	float ElapsedTime = 0.0f;
	bool Exploded = false;
	bool CollisionOvelap = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void BombExplode();
	void IncreaseBlastDistance(int IncreaseBy) { BlastDistance += IncreaseBy; }
	void CauseDamageInLine(FVector Start, FVector Direction);
	UDestructibleComponent* DestructibleComponent;
	UParticleSystem* ParticleSystem;
};
