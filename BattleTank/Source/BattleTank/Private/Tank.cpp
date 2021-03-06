// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Components/SceneComponent.h"
#include "UObject/UnrealType.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"





// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	/*TankBody = CreateDefaultSubobject<UStaticMeshComponent>(FName("Tank Body"));
	SetRootComponent(TankBody);
	TankBody->SetNotifyRigidBodyCollision(true);
	TankBody->SetVisibility(true);

	DeathSmoke = CreateDefaultSubobject<UParticleSystemComponent>(FName("Death Smoke"));
	DeathSmoke->SetupAttachment(RootComponent);
	DeathSmoke->bAutoActivate = false;*/

	//No need to protect pointers
	
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
	
	

}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<float>(DamagePoints, 0, CurrentHealth);
	CurrentHealth = CurrentHealth - DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	
	return DamageToApply;
}

float ATank::GetHealthPercent() const
{
	
	return (float)CurrentHealth / (float)StartingHealth;
}


