// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "CapsulaActor.generated.h"

/**
 * 
 */
UCLASS()
class STAR_FIGHTERSD_API ACapsulaActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	ACapsulaActor();
private:


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PickUp();
	virtual void PutDown(FTransform TargetLocation);
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MoveSpeed;
	float MovingX;
	float MovingY;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Datos", meta = (AllowPrivateAccess="true"))
	FString InventoryActorName;
public:
	FORCEINLINE FString GetInventoryActorName() const { return InventoryActorName; }
	FORCEINLINE void SetInventoryActorName( const FString _InventoryActorName ){  InventoryActorName= _InventoryActorName; }


};
