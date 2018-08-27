// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "GameFramework/Actor.h"
//#include "Engine/World.h" //debug testing to provide time
#include "Components/SceneComponent.h"
#include "ControlPointMeshComponent.h"
//#include "DrawDebugHelpers.h" //debug testing to p rovide line drawing
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"



// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO Should this really tick?

	// ...
}
void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;

}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)//calculate velocity
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aim Solution found target: %s"), *OutHitLocation.ToString());
		/*DrawDebugLine
		(
			GetWorld(),
			StartLocation,
			OutHitLocation,
			FColor(255, 0, 0),
			false,
			0.0f,
			0.0f,
			10.0f
		);*/
		MoveBarrelTowards(AimDirection);
		
	}
	else
	{
		/*auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f No aim solution found"),Time);*/
	}
	//if no solution found do nothing 
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//get current location of barrel and desired placement of barrel, calculate the shortest distance to that point and move
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	
	
	Barrel->Elevate(5); //TODO remove magic number

}

