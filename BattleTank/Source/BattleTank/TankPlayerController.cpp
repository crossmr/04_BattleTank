// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "BattleTank.h"




void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing %s"), *(ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));
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
		//TODO tell tank to aim at this point
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *OutHitLocation.ToString());
	}
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::bGetSightRayHitLocation(FVector& OutHitLocation ) const
{
	//find crosshair position
	int32 ViewportSizeX, ViewPortSizeY;
	GetViewportSize(ViewportSizeX, ViewPortSizeY);
	//UE_LOG(LogTemp, Warning, TEXT("ViewPortSizeX: %s"), *(FString::FromInt(ViewportSizeX)));
	//UE_LOG(LogTemp, Warning, TEXT("ViewPortSizeY: %s"), *(FString::FromInt(ViewPortSizeY)));
	auto ScreenLocation = FVector2D((ViewportSizeX -(ViewportSizeX*CrossHairXLocation)), (ViewPortSizeY-(ViewPortSizeY*CrossHairYLocation)));
	//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *ScreenLocation.ToString());
	//Deproject the screen position of crosshair to a world direction
	//line trace through that direction
	//see what hits up to maximum range

	return true;
}