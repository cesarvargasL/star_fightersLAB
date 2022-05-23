// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTerrestre2.h"

AEnemigoTerrestre2::AEnemigoTerrestre2()
{
}

void AEnemigoTerrestre2::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(rand(), 0.0f, 20.0f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = Movement.Rotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
	}
}
