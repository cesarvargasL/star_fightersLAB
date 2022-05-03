// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Nave.generated.h"


UCLASS()
class STAR_FIGHTERSD_API ANave : public APawn
{
	GENERATED_BODY()
	/*Se pone la malla a la clase padre para que asi todas las neves puedan tener visibilidad 
	en el Unreal*/

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShipMeshComponent;

public:
	// Sets default values for this pawn's properties
	ANave();
	/*Se pone esta propiedad en la clase padre porque
	(es propia de esta) es el movimiento y velocidad de la nave*/
	/* The speed our ship moves around the level */
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;

	//Sound to PLay Each time we fire
	UPROPERTY(Category = Audio, EditAnywhere, BlueprintReadWrite)
		class USoundBase* FireSound;

	/*The energy ship*/
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
		float Energy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class UStaticMeshComponent* GetShipMeshComponent() const { return ShipMeshComponent; }


};
