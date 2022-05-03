// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo2.h"

AEnemigoAereo2::AEnemigoAereo2()
{

}

void AEnemigoAereo2::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaSeconds) - FMath::Sin(RunningTime));
	NewLocation.Y += DeltaHeight * SpeedScale;
	RunningTime += DeltaSeconds;
	SetActorLocation(NewLocation);
}
