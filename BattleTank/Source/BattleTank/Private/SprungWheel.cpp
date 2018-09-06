// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	SetRootComponent(Mass);
	Mass->SetSimulatePhysics(true);
	Mass->SetMassOverrideInKg(FName("MassBone"), 40000, true);


	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(RootComponent);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetMassOverrideInKg(FName("WheelBone"), 500, true);

	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("PhysicsConstraint"));
	PhysicsConstraint->SetupAttachment(RootComponent);
	PhysicsConstraint->SetConstrainedComponents(Mass, FName("MassBone"), Wheel, FName("WheelBone"));
	PhysicsConstraint->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0);
	PhysicsConstraint->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);
	PhysicsConstraint->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	PhysicsConstraint->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	PhysicsConstraint->SetLinearPositionDrive(false, false, true);
	PhysicsConstraint->SetLinearVelocityDrive(false, false, true);
	PhysicsConstraint->SetLinearDriveParams(5000.f, 2000.f, 0.f);


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

