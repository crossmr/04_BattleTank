// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force and to apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	//Maxforce per track in newtons
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 40000000; //assume 40 tonne tank and 1g acceleration
	
private:
	UTankTrack();

	void DriveTrack(float CurrentThrottle);

	TArray<class ASprungWheel*> GetWheels() const;

};
