// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoTerrestre1.h"

AEnemigoTerrestre1::AEnemigoTerrestre1()
{
	SpeedScale = 300.0f;
}

void AEnemigoTerrestre1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Y += DeltaHeight * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
	
	FVector NewLocation1 = GetActorLocation();
	float DeltaForward = (FMath::Cos(RunningTime + DeltaTime) - FMath::Cos(RunningTime));
	NewLocation1.X += DeltaForward * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation1 );
}
