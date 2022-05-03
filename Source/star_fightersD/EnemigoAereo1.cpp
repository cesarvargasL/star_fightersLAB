// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemigoAereo1.h"


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


