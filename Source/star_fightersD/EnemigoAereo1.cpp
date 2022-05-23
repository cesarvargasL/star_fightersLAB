// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo1.h"
#include "Proyectil0.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemigoAereo1::AEnemigoAereo1()
{
	SpeedScale = 0.0f;
}

void AEnemigoAereo1::Tick(float DeltaTime)
{
	//FUNCIONES MATEMATICAS PARA HACER MOVER ALA NAVE
	//Super::Tick(DeltaTime);
		//FVector NewLocation = GetActorLocation();
	//float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	//NewLocation.Y += DeltaHeight * SpeedScale;
	//RunningTime += DeltaTime;
	//SetActorLocation(NewLocation);

	/*FVector NewLocation1 = GetActorLocation();
	float DeltaForward = (FMath::Cos(RunningTime + DeltaTime) - FMath::Cos(RunningTime));
	NewLocation1.X += DeltaForward * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation1 );*/


	//TICK  es el movimiento por fotograma 
	Super::Tick(DeltaTime);
	//Se crea un vector "Nueva Localizacion
	//Para poder acceder a al eje Y hacer el movimiento alli 
	//el SpeedScale es la velocidad para mover la nave del cual se le puede dar valor desde el codigo o el unreal
	//DelatHeight aborda el ajuste cuadro por cuadro que queremos, se atribuye a NewLocation.Y
	//por lo que estamos ajustando el componente vertical de la posición del actor con el que estamos trabajando.
	FVector NewLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Y += DeltaHeight * SpeedScale;
	RunningTime += DeltaTime;
	SetActorLocation(NewLocation);
	
}

void AEnemigoAereo1::Fire()
{
	//UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(rand(), 0.0f, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	FireShot(FireDirection);
}

void AEnemigoAereo1::FireShot(FVector FireDirection)
{
	if (bCanFire == true)
	{

		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// spawn the projectile
				World->SpawnActor<AProyectil0>(SpawnLocation, FireRotation);
			}



			//bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AEnemigoAereo1::ShotTimerExpired, FireRate);
			//try and play the sound if specified

			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;

		}
	}

}

void AEnemigoAereo1::ShotTimerExpired()
{
	bCanFire = true;
}


