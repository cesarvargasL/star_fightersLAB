// Fill out your copyright notice in the Description page of Project Settings.

#include "CapsulaComponent.h"
// Sets default values for this component's properties
UCapsulaComponent::UCapsulaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCapsulaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCapsulaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UCapsulaComponent::AddToInventory(ACapsulaActor* ActorToAdd)
{
	return ShipInventory.Add(ActorToAdd);
}

void UCapsulaComponent::RemoveFromInventory(ACapsulaActor* ActorToRemove)
{
	ShipInventory.Remove(ActorToRemove);
}

