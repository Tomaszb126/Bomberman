// Fill out your copyright notice in the Description page of Project Settings.

#include "NPCPawn.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "MyPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Bomb.h"


// Sets default values
ANPCPawn::ANPCPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Get Bomb mesh and set default settings
	UDestructibleComponent* DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("NPC"));
	RootComponent = DestructibleComponent;
	//DestructibleComponent->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	DestructibleComponent->SetMobility(EComponentMobility::Movable);

	ConstructorHelpers::FObjectFinder<UDestructibleMesh> 
		DestructibleMeshAsset(TEXT("DestructibleMesh'/Game/Shape_Sphere_NPC_DM.Shape_Sphere_NPC_DM'"));
	if (DestructibleMeshAsset.Succeeded()) {
		DestructibleComponent->SetWorldScale3D(FVector(0.7f));
		DestructibleComponent->SetSkeletalMesh(DestructibleMeshAsset.Object);
	}

	DestructibleComponent->OnComponentHit.AddDynamic(this, &ANPCPawn::NPCHit);
	DestructibleComponent->OnComponentFracture.AddDynamic(this, &ANPCPawn::OnNPCDestroy);

	ColliderSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ColliderSphere"));
	ColliderSphere->SetupAttachment(RootComponent);
	ColliderSphere->SetWorldScale3D(FVector(10.0f));

	NPCMovementComponent = CreateDefaultSubobject<UMyPawnMovementComponent>(TEXT("CustomNPCMovementComponent"));
	NPCMovementComponent->UpdatedComponent = RootComponent;
	NPCMovementComponent->IncreaseSpeedMultiplier(-0.5f);
}

	// Called when the game starts or when spawned
void ANPCPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Fractured) {
		TSet<AActor*> OverlappingActors;
		ColliderSphere->GetOverlappingActors(OverlappingActors, AMyPawn::StaticClass());

		for (auto &Element : OverlappingActors) {
			FVector DirectionToPlayer = Element->GetActorLocation() - GetActorLocation();
			DirectionToPlayer = DirectionToPlayer.GetSafeNormal();

			//UE_LOG(LogTemp, Warning, TEXT("Direction to player - x: %f , y: %f"), DirectionToPlayer.X, DirectionToPlayer.Y);

			FHitResult Impact;
			FVector LineStart = GetActorLocation() + (DirectionToPlayer * 50.0f);
			FVector LineEnd = Element->GetActorLocation();
			FCollisionQueryParams CollisonParams;

			//DrawDebugLine(GetWorld(), LineStart, LineEnd, FColor::Red, false);

			// Check line of sight to player
			bool isHit = GetWorld()->LineTraceSingleByChannel(Impact, LineStart, LineEnd, 
				ECC_Visibility, CollisonParams);
			if (Impact.GetActor()->IsA(AMyPawn::StaticClass()) || 
				Impact.GetActor()->IsA(ABomb::StaticClass()) || 
				Impact.GetActor()->IsA(ANPCPawn::StaticClass()))
			{
				UE_LOG(LogTemp, Warning, TEXT("Chase player"));
				if (NPCMovementComponent && (NPCMovementComponent->UpdatedComponent == RootComponent))
					NPCMovementComponent->AddInputVector(DirectionToPlayer + FVector(0.0f, 0.0f, -1.0f));
			}
		}
	}
	else {
		ElapsedTime += DeltaTime;
		if (ElapsedTime >= 1.0f)
			Destroy();
	}
}

// Called to bind functionality to input
void ANPCPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UPawnMovementComponent * ANPCPawn::GetMovementComponent() const
{
	return NPCMovementComponent;
}

void ANPCPawn::NPCHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, 
	UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->IsA(AMyPawn::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Player hit"));
		UGameplayStatics::ApplyPointDamage(OtherActor, 10.0f, GetActorLocation(), 
			Hit, GetInstigatorController(), this, UDamageType::StaticClass());
	}
}

void ANPCPawn::OnNPCDestroy(const FVector & HitPoint, const FVector & HitDirection)
{
	Fractured = true;
}
