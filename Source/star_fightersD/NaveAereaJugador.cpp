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

	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = false;

	FireForwardValue = 1.0f;
	FireRightValue = 0.0f;
	
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

		//	if (Hit.IsValidBlockingHit())
		//	{
		//		const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
		//		const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
		//		RootComponent->MoveComponent(Deflection, NewRotation, true);
		//	}
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




