// Fill out your copyright notice in the Description page of Project Settings.


#include "CapsulaActor.h"
#include "NaveaereaJugador.h"

ACapsulaActor::ACapsulaActor() :Super()
  
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	auto MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile'"));
	if (MeshAsset.Object != nullptr)
	{
		GetStaticMeshComponent()->SetStaticMesh(MeshAsset.Object);
		GetStaticMeshComponent()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	}
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
	SetActorEnableCollision(true);
	
	//SpeedScale = 300.0f;
	MoveSpeed = 100.0f;
	MovingX = 0.0f;
	MovingY = 0.0f;
}

void ACapsulaActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACapsulaActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	srand(time(NULL));

	MovingX = rand() % 20 - 10;
	MovingY = rand() % 20 - 10;

	MoveSpeed = 50;

	const FVector MoveDirection = FVector(MovingX, MovingY, 0.0f);
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();

		FHitResult Hit(1.0f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}

}

void ACapsulaActor::PickUp()
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ACapsulaActor::PutDown(FTransform TargetLocation)
{
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorLocation(TargetLocation.GetLocation());
}
