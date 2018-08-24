// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/TankAIController.h"
#include "BattleTank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("AIController Targetting: %s"), *(PlayerTank->GetName()));
	}
	
}

ATank * ATankAIController::GetControlledAITank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		//TODO Move towards player

		//Aim Towards Player
		GetControlledAITank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
	}

	
}
