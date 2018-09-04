// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "GameFramework/Actor.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack * RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendRotateClockwise(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	//no need to call super as we are replacing functionality

	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightTurn = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendRotateClockwise(RightTurn);

}

void UTankMovementComponent::Reset()
{
	FVector CurrentPosition = GetOwner()->GetActorLocation();
	FVector NewLocation = FVector(CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z + 100.f);
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	FRotator NewRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, 0.0f);
	GetOwner()->SetActorLocationAndRotation(NewLocation, NewRotation, false);
}

