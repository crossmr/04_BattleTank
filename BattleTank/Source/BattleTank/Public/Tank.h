// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//called by the engine when actor is damaged
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//Returns CurrentHealth as a percentage of starting health between 0 and 1
	UFUNCTION(BlueprintPure, Category="Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;


private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; //Initialized in begin play


protected:


	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* TankBody = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* DeathSmoke = nullptr;


};
