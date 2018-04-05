

#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bomb.h"
#include "Engine/World.h"
#include "ParticleDefinitions.h"
#include "MyPawnMovementComponent.h"
#include "EngineUtils.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// RootComponent
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Root Comp"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	// CameraComponent
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));
	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-100.0f, 0.0f, 700.0f));
	OurCamera->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

	// StaticMesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Our Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> PawnMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (PawnMeshAsset.Succeeded()) {
		StaticMesh->SetStaticMesh(PawnMeshAsset.Object);
		StaticMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		StaticMesh->SetWorldScale3D(FVector(1.0f));
	}

	// Create a particle system that we can activate or deactivate
	OurParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MovementParticles"));
	OurParticleSystem->SetupAttachment(StaticMesh);
	OurParticleSystem->bAutoActivate = false;
	OurParticleSystem->SetRelativeLocation(FVector(-20.0f, 0.0f, 20.0f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		OurParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create an instance of our movement component, and tell it to update our root component.
	OurMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("CustomMovementComponent"));
	OurMovementComponent->bConstrainToPlane = true;
	OurMovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);

	InputComponent->BindAction("SpawnBomb", IE_Pressed, this, &AMyPawn::PlaceBomb);
	InputComponent->BindAction("Explosion", IE_Pressed, this, &AMyPawn::CauseExplosion);

}

UPawnMovementComponent* AMyPawn::GetMovementComponent() const
{
	return OurMovementComponent;
}

void AMyPawn::MoveForward(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorForwardVector() * AxisValue + FVector(0.0f, 0.0f,-1.0f));
	}
}

void AMyPawn::MoveRight(float AxisValue)
{
	if (OurMovementComponent && (OurMovementComponent->UpdatedComponent == RootComponent))
	{
		OurMovementComponent->AddInputVector(GetActorRightVector() * AxisValue);
	}
}

void AMyPawn::PlaceBomb()
{
	int BombCount = 0;
	for (TActorIterator<ABomb> BombItr(GetWorld()); BombItr; ++BombItr) {
		BombCount++;
	}
	if (BombCount >= MaxBombs) return ;

	FVector BombPosition = FVector(0.0f, 0.0f, -50.0f) + GetActorLocation();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ABomb>(BombPosition, Rotation, SpawnInfo);

}

void AMyPawn::CauseExplosion()
{
	if (OurParticleSystem && OurParticleSystem->Template)
	{
		OurParticleSystem->ToggleActive();
	}
}
