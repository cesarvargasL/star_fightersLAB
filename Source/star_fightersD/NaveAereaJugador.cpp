// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveAereaJugador.h"
#include "Proyectil0.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

//MOVEFORWARD ES UNA VARIABLE DE TIPO texto
const FName ANaveAereaJugador::MoveForwardBinding("MoveForward");
const FName ANaveAereaJugador::MoveRightBinding("MoveRight");

ANaveAereaJugador::ANaveAereaJugador()
{

	// Cache or sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("SoundWave'/Game/TwinStick/Audio/TwinStickFire.TwinStickFire'"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm


	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;

	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;


	NaveInventory = CreateDefaultSubobject<UCapsulaComponent>("MyInventory");
	//Ship Info
	//NaveInfo.Add("Vida aumentada", 100);
	//NaveInfo.Add("Vida ", 100);
	NaveInfo.Add("velocidad", 0);
	NaveInfo.Add("velocidadDI", 0);
	NaveInfo.Add("Proyectil", 0);

	
}

void ANaveAereaJugador::Tick(float DeltaSeconds)
{
		// Find movement direction
		//devuelve el valor de la teclas que tienen el moveforward 
		const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
		const float RightValue = GetInputAxisValue(MoveRightBinding);

		if (ForwardValue != 0.0f || RightValue != 0.0f) {

			if (ForwardValue != FireForwardValue) {
				FireForwardValue = ForwardValue;
			}

			if (RightValue != FireRightValue) {
				FireRightValue = RightValue;
			}
		}

		// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
		const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

		// Calculate  movement
		const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;

		// If non-zero size, move this actor
		if (Movement.SizeSquared() > 0.0f)
		{
			const FRotator NewRotation = Movement.Rotation();
			FHitResult Hit(1.f);
			RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		}
}

		

void ANaveAereaJugador::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	/*Aqui pasa que agrege al payer input component , los valores de moveforwrd*/

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ANaveAereaJugador::Fire);
	PlayerInputComponent->BindAction(TEXT("DropItem"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::DropItem);
	PlayerInputComponent->BindAction(TEXT("Inventory"), EInputEvent::IE_Pressed, this, &ANaveAereaJugador::Inventory);
	PlayerInputComponent->BindAction(TEXT("Test"), IE_Pressed, this, &ANaveAereaJugador::Test);
	PlayerInputComponent->BindAction(TEXT("velocidad"), IE_Pressed, this, &ANaveAereaJugador::velocidad);
	PlayerInputComponent->BindAction(TEXT("velocidadDI"), IE_Pressed, this, &ANaveAereaJugador::velocidadDI);
}
void ANaveAereaJugador::velocidad()
{
	FString v = "velocidad";
	//
	for (auto& pair : NaveInfo) {

		if (pair.Key == v) {

			if (pair.Value > 0) {
				pair.Value = pair.Value + 1;
				MoveSpeed = MoveSpeed + 400;
			}
			break;
		}
	}
}
void ANaveAereaJugador::velocidadDI()
{
	FString v = "velocidadDI";
	//
	for (auto& pair : NaveInfo) {

		if (pair.Key == v) {

			if (pair.Value > 0) {
				pair.Value = pair.Value - 1;
				MoveSpeed = MoveSpeed - 350;
			}
			break;
		}
	}
}
void ANaveAereaJugador::Fire()
{
	bCanFire = true;
	UE_LOG(LogTemp, Warning, TEXT("Se presiono la barra espaciadora"));
	// Create fire direction vector

	UE_LOG(LogTemp, Warning, TEXT("FireForwardValue: %f FireRightValue: %f"), FireForwardValue, FireRightValue);
	const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	//const FVector FireDirection = GetActorLocation();
	// Try and fire a shot
	FireShot(FireDirection);
}

void ANaveAereaJugador::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
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
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &ANaveAereaJugador::ShotTimerExpired, FireRate);
			//try and play the sound if specified
				
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		
		}
	}
}

void ANaveAereaJugador::ShotTimerExpired()
{
	bCanFire = true;
}


void ANaveAereaJugador::TakeItem(ACapsulaActor* InventoryItem)
{
	InventoryItem->PickUp();
	NaveInventory->AddToInventory(InventoryItem);
}

void ANaveAereaJugador::DropItem()
{
	if (NaveInventory->ShipInventory.Num() == 0)
	{
		return;
	}
	ACapsulaActor* Item = NaveInventory->ShipInventory.Last();
	NaveInventory->RemoveFromInventory(Item);
	//should probably use scaled bounding box
	FVector ItemOrigin;
	FVector ItemBounds;
	Item->GetActorBounds(false, ItemOrigin, ItemBounds);
	FTransform PutDownLocation = GetTransform() + FTransform(RootComponent->GetForwardVector() * ItemBounds.GetMax());
	Item->PutDown(PutDownLocation);
}

void ANaveAereaJugador::Inventory()
{
	//for(int32 i=0 ; i<NaveInventory->ShipInventory.Num(); i++) {
		//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("Actor de nombre: %s"), *(NaveInventory->ShipInventory[i]->GetInventoryActorName())));
	//}
	for (auto& Elem : NaveInfo) {
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));
	}
}

void ANaveAereaJugador::Test()
{
	TSet<int>EjemploSet;
	EjemploSet.Add(1);
	EjemploSet.Add(2);
	EjemploSet.Add(3);
	EjemploSet.Add(1);  //duplicate: won't be addeed
	EjemploSet.Add(1);  //duplicate: won't be addeed

	for (auto It = EjemploSet.CreateConstIterator(); It; ++It) {

		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%d"), *It));
	}
}

void ANaveAereaJugador::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	for (auto& Elem : NaveInfo) {
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, FString::Printf(TEXT("%s = %d"), *Elem.Key, Elem.Value));
	}

	ACapsulaActor* MyInventoryItem = Cast<ACapsulaActor>(Other);
	if (MyInventoryItem != nullptr)
	{
		FString n = MyInventoryItem->GetInventoryActorName();

		for (auto& pair : NaveInfo) {
			if (pair.Key == n) {
				pair.Value = pair.Value + 1;
				break;
			}
		}

		TakeItem(MyInventoryItem);

	}
}




