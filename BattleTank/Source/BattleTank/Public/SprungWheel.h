// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Axle1 = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent* Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* MainSpring = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UPhysicsConstraintComponent* AxleConstraint = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SetupConstraints();

	
	
};
