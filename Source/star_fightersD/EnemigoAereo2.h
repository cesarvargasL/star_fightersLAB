// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "EnemigoAereo2.generated.h"

/**
 * 
 */
UCLASS()
class STAR_FIGHTERSD_API AEnemigoAereo2 : public ANaveAerea
{
	GENERATED_BODY()
	
public:
	AEnemigoAereo2();

	// Static names for axis bindings
	//static const FName MoveForwardBinding;
	//static const FName SpeedScale;

public:
	virtual void Tick(float DeltaSeconds) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		float SpeedScale;
	float RunningTime;
};
