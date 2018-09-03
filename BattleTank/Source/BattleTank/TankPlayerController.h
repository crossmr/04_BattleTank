// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;


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

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent * AimCompRef);

	UPROPERTY(BlueprintReadOnly)
		UTankAimingComponent* TankAimingComponent = nullptr;



		
public:


	bool bGetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const;

	void BeginPlay() override;
		
	void Tick(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float CrossHairYLocation = 0.3333;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float LineTraceRange = 1000000;
};
