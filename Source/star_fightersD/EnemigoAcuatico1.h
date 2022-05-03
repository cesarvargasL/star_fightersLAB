// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAcuatica.h"
#include "EnemigoAcuatico1.generated.h"

/**
 * 
 */
UCLASS()
class STAR_FIGHTERSD_API AEnemigoAcuatico1 : public ANaveAcuatica
{
	GENERATED_BODY()

public:
	AEnemigoAcuatico1();
public:
	virtual void Tick(float DeltaSeconds) override;
	float SpeedScale;
	float RunningTime;
	
};
