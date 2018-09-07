// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MainSpring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Main Spring"));
	SetRootComponent(MainSpring);
	
	Axle1 = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle1->SetupAttachment(RootComponent);

	AxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleConstraint->SetupAttachment(Axle1);
		
	
	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle1);


	


}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	SetupConstraints();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::SetupConstraints()
{
	if (!GetAttachParentActor()) { return; }
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) { return; }
	MainSpring->SetConstrainedComponents(Axle1, NAME_None, BodyRoot, NAME_None);
	AxleConstraint->SetConstrainedComponents(Axle1, NAME_None, Wheel, NAME_None);
}


