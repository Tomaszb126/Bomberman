// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "DestructibleWall.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine.h"
#include "Containers/UnrealString.h"
#include "MyPawn.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get Bomb mesh and set default settings
	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("BOMB"));
	RootComponent = DestructibleComponent;
	DestructibleComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	DestructibleComponent->SetMobility(EComponentMobility::Movable);

	ConstructorHelpers::FObjectFinder<UDestructibleMesh> DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Sphere_Bomb_DM.Shape_Sphere_Bomb_DM'"));
	if (DestructibleMeshAsset.Succeeded()) {
		DestructibleComponent->SetWorldScale3D(FVector(0.6f));
		DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);
	}

	// Get Particle for explosion
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (ParticleAsset.Succeeded())
	{
		ParticleSystem = ParticleAsset.Object;
	}
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

	// Get blast distance from Player
	TArray<AActor*> Pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyPawn::StaticClass(), Pawns);
	BlastDistance = Cast<AMyPawn>(Pawns[0])->GetBombBlastRange();
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	// After 0.5s turn on collisions
	// After 3s detonate
	// After 4s destroy actor
	Super::Tick(DeltaTime);
	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 0.5f && CollisionOvelap) {
		CollisionOvelap = false;
		DestructibleComponent->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	}
	/*
	if (ElapsedTime >= 2) {
		ConstructorHelpers::FObjectFinder<UMaterialInterface> DestructibleMeshAsset(TEXT("Material'/Game/M_Metal_Steel_Red.M_Metal_Steel_Red'"));
		if (DestructibleMeshAsset.Succeeded()) {
			DestructibleComponent->SetMaterial(0, DestructibleMeshAsset.Object);
			DestructibleComponent->SetWorldScale3D(FVector(0.8f));
		}
	}
	*/
	if (ElapsedTime >= Lifetime && !Exploded) BombExplode();
	if (ElapsedTime >= 4.0f) this->Destroy();

}
void ABomb::BombExplode()
{
	// Create explosion
	UE_LOG(LogTemp, Warning, TEXT("Granat dsadbum"));
	// Destroy bomb itself
	DestructibleComponent->ApplyDamage(100.0f, GetActorLocation(), FVector(0.0f, 0.0f, -1.0f), 1.0f);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation() + FVector(0.0f, 0.0f, 40.0f), FRotator::ZeroRotator, true);

	FVector BombOrigin, BombExtent;
	GetActorBounds(false, BombOrigin, BombExtent);

	// Create explosion in 4 directions
	FVector Start, Direction;
	// Forward
	Start = GetActorLocation() + FVector(BombExtent.X, 0.0f, BombExtent.Z);
	Direction = FVector(1.0f, 0.0f, 0.0f);
	CauseDamageInLine(Start, Direction);

	// Back
	Start = GetActorLocation() + FVector(-BombExtent.X, 0.0f, BombExtent.Z);
	Direction = FVector(-1.0f, 0.0f, 0.0f);
	CauseDamageInLine(Start, Direction);

	// Right
	Start = GetActorLocation() + FVector(0.0f, BombExtent.Y, BombExtent.Z);
	Direction = FVector(0.0f, 1.0f, 0.0f);
	CauseDamageInLine(Start, Direction);

	// Left
	Start = GetActorLocation() + FVector(0.0f, -BombExtent.Y, BombExtent.Z);
	Direction = FVector(0.0f, -1.0f, 0.0f);
	CauseDamageInLine(Start, Direction);

	Exploded = true;

}

void ABomb::CauseDamageInLine(FVector Start, FVector Direction)
{
	FHitResult Impact;
	FVector End = (Direction * BlastDistance) + Start;
	FCollisionQueryParams CollisonParams;

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, true);

	// Hit first element on explosions way
	bool isHit = GetWorld()->LineTraceSingleByChannel(Impact, Start, End, ECC_Visibility, CollisonParams);
	if (isHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bomb hit"));
		if (Impact.bBlockingHit)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Actor hit: %s"), *Impact.GetActor()->GetName()));

			FDamageEvent DamageEvent;
			UGameplayStatics::ApplyPointDamage(Impact.GetActor(), 10.0f, GetActorLocation(), Impact, GetInstigatorController(), this, UDamageType::StaticClass());
		}
	}

	// Create explosion particles along blast way
	for (int i = 0; i < BlastDistance/100; i++) {
		UE_LOG(LogTemp, Warning, TEXT("explosion boom, distance: %f"), Impact.Distance);
		// Dont create particles after it hit something
		if(Impact.Distance <=0 || Impact.Distance >= i*100)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation() + (Direction*(i+1)*100) + FVector(0.0f,0.0f,40.0f), FRotator::ZeroRotator, true);
	}
}


