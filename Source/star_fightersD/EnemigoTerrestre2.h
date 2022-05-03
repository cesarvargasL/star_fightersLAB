// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NaveTerrestre.h"
#include "EnemigoTerrestre2.generated.h"

/**
 * 
 */
UCLASS()
class STAR_FIGHTERSD_API AEnemigoTerrestre2 : public ANaveTerrestre
{
	GENERATED_BODY()
public:
	AEnemigoTerrestre2();

public:
	virtual void Tick(float DeltaSeconds) override;

};