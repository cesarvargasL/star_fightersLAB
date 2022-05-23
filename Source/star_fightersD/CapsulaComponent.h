// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CapsulaActor.h"
#include "CapsulaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STAR_FIGHTERSD_API UCapsulaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCapsulaComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		TArray<ACapsulaActor*> ShipInventory;

	UFUNCTION()
		int32 AddToInventory(ACapsulaActor* ActorToAdd);

	UFUNCTION()
		void RemoveFromInventory(ACapsulaActor* ActorToRemove);
};
