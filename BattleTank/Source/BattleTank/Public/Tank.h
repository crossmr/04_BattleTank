// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Templates/Casts.h"
#include "Tank.generated.h"

class UTankBarrel; //Forward declaration
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();

//	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000; //TODO Find sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UTankBarrel * Barrel = nullptr; //TODO Remove
	
	double LastFireTime = 0;

protected:
	virtual void BeginPlay() override;
	
};
