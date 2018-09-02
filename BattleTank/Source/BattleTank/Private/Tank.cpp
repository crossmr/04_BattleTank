// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Components/SceneComponent.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"




// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//No need to protect pointers
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("BOMI: %s Tank Constructor"), *Name)
}

void ATank::BeginPlay()
{
	Super::BeginPlay(); //needed for BP begin play to work
	auto Name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("BOMI: %s Tank BeginPlay"), *Name)
}

void ATank::AimAt(FVector OutHitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(OutHitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded) 
	{

		auto SocketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		auto SocketRotation = Barrel->GetSocketRotation(FName("Projectile"));

		//spawn projectile at the socket location on the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, SocketLocation, SocketRotation);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}