

#include "MyPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Bomb.h"
#include "Engine/World.h"
#include "ParticleDefinitions.h"

// Sets default values
AMyPawn::AMyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));

	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Our Camera"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Our Mesh"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-100.0f, 0.0f, 700.0f));
	OurCamera->SetRelativeRotation(FRotator(-70.0f, 0.0f, 0.0f));

	OurVisibleComponent->SetupAttachment(RootComponent);
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

	{
		if (!CurrentVelocity.IsZero()) {
			FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(NewLocation);
		}
	}

}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveRight", this, &AMyPawn::Move_YAxis);

	InputComponent->BindAction("SpawnBomb", IE_Pressed, this, &AMyPawn::PlaceBomb);
	InputComponent->BindAction("Explosion", IE_Pressed, this, &AMyPawn::CauseExplosion);

}

void AMyPawn::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}

void AMyPawn::Move_YAxis(float AxisValue)
{

	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}

void AMyPawn::PlaceBomb()
{
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<ABomb>(GetActorLocation(), Rotation, SpawnInfo);

}

void AMyPawn::CauseExplosion()
{
	UParticleSystem* PS = CreateDefaultSubobject<UParticleSystem>(TEXT("Explosion"));
}
