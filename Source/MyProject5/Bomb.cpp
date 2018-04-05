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

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb Mesh"));

	//ConstructorHelpers::FObjectFinder<UStaticMesh> BombMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	//mesh->SetStaticMesh(BombMesh.Object);


	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("BOMB"));
	RootComponent = DestructibleComponent;
	DestructibleComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	DestructibleComponent->SetMobility(EComponentMobility::Movable);
	//Mesh
	ConstructorHelpers::FObjectFinder<UDestructibleMesh> DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Sphere_Bomb_DM.Shape_Sphere_Bomb_DM'"));
	if (DestructibleMeshAsset.Succeeded()) {

		DestructibleComponent->SetWorldScale3D(FVector(0.6f));
		DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);
	}

	//SetLifeSpan(3.0f);
	// Create a particle system that we can activate or deactivate
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(DestructibleComponent);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 40.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	//RootComponent = mesh;

	//this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ElapsedTime += DeltaTime;
	if (ElapsedTime >= 1 && CollisionOvelap) {
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
	if (ElapsedTime >= 4) this->Destroy();

}
void ABomb::BombExplode()
{
	// Create explosion
	UE_LOG(LogTemp, Warning, TEXT("Granat dsadbum"));
	//DestructibleComponent->ApplyDamage(100.0f, GetActorLocation(), FVector(0.0f, 0.0f, -1.0f), 1.0f);
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}

	for (TActorIterator<ADestructibleWall> it(GetWorld()); it; ++it)
	{

		UGameplayStatics::ApplyRadialDamage(GetWorld(), 100, GetActorLocation() + FVector(0.0f,0.0f,-20.0f), BlastDistance, UDamageType::StaticClass(), TArray<AActor*>());
	}
	
	Exploded = true;

}


