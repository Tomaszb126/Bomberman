// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "MyPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "EngineUtils.h"
#include "Engine.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Pickup"));
	RootComponent = Root;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	//RootComponent = MeshComponent;
	MeshComponent->SetupAttachment(RootComponent);

	UBoxComponent* Box = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupBox"));
	Box->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));
	Box->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnPlayerPickup);
	Box->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::OnPlayerPickup(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && (OtherActor->IsA(AMyPawn::StaticClass()))) {
		for (TActorIterator<AMyPawn> PlayerItr(GetWorld()); PlayerItr; ++PlayerItr) {
			PlayerItr->MaxBombs++;

			UE_LOG(LogTemp, Warning, TEXT("Granat dsadbum %d"), PlayerItr->MaxBombs);
			FString pickup = FString::Printf(TEXT("Picked up bomb upgrade. Max bombs: %d"), PlayerItr->MaxBombs);
			GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Red, pickup);
		}
		Destroy();
	}
}

