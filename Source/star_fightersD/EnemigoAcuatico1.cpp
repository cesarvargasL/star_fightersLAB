// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAcuatico1.h"

AEnemigoAcuatico1::AEnemigoAcuatico1()
{
	SpeedScale = 50.0f;
}

void AEnemigoAcuatico1::Tick(float DeltaTime)
{
	FVector NewLocation = GetActorLocation();
	float DeltaForward = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaForward * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
}
