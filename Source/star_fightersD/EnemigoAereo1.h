// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveAerea.h"
#include "EnemigoAereo1.generated.h"

/**
 * 
 */
UCLASS()
class STAR_FIGHTERSD_API AEnemigoAereo1 : public ANaveAerea
{
	GENERATED_BODY()
	

public:
	AEnemigoAereo1();

	// Static names for axis bindings
	//static const FName MoveForwardBinding;
	//static const FName SpeedScale;
private:
	/* Flag to control firing  */
	uint32 bCanFire : 1;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle TimerHandle_ShotTimerExpired;

public:
	virtual void Tick(float DeltaSeconds) override;
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		float SpeedScale;
		float RunningTime;
		void Fire();

		/* Fire a shot in the specified direction */
		void FireShot(FVector FireDirection);

		/* Handler for the fire timer expiry */
		void ShotTimerExpired();
		/** Offset from the ships location to spawn projectiles */
		UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
			FVector GunOffset;

		/* How fast the weapon will fire */
		UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
			float FireRate;

};
