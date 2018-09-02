// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find aiming Component"))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("I'm ticking"))
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector OutHitLocation; //Out parameter
	if (bGetSightRayHitLocation(OutHitLocation)) //is going to line trace later
	{
		GetControlledTank()->AimAt(OutHitLocation);
		//TODO tell tank to aim at this point
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::bGetSightRayHitLocation(FVector& OutHitLocation ) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewPortSizeY;
	GetViewportSize(ViewportSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);
	//auto ScreenLocation = FVector2D((ViewportSizeX -(ViewportSizeX*CrossHairXLocation)), (ViewPortSizeY-(ViewPortSizeY*CrossHairYLocation)));
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *ScreenLocation.ToString());
	//Deproject the screen position of crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//line trace through that direction
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	//see what hits up to maximum range

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation,  
		LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector MaximumRange = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		MaximumRange,
		ECollisionChannel::ECC_Visibility)
		)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0.0f);
	return false;
}