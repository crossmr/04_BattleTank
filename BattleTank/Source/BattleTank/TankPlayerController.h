// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:

	//start the tank moving the barrel so that a shot will hit where 
	//the crosshair intersects the world

	void AimTowardsCrosshair();


		
public:
	ATank * GetControlledTank() const;

	bool bGetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	void BeginPlay() override;
		
	void Tick(float DeltaTime);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrossHairYLocation = 0.3333;
};
