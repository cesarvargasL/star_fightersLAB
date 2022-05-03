// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveTerrestre.h"
#include "EnemigoTerrestre1.generated.h"

/**
 * 
 */
UCLASS()
class STAR_FIGHTERSD_API AEnemigoTerrestre1 : public ANaveTerrestre
{
	GENERATED_BODY()
	
public:
	AEnemigoTerrestre1();

public:
	virtual void Tick(float DeltaSeconds) override;

	float SpeedScale;
	float RunningTime;
};
