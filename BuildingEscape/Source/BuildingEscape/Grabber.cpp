// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	GetRequiredObjects();
	
}

// Get required objects
void UGrabber::GetRequiredObjects()
{
	World = GetWorld();
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	/// Get and set InputComponent
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (Input)
	{
		Input->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component not found by %s Class"), *this->GetName());
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get the Player Viewpoint from World - location and rotation - and return them, output results - OUT
	World->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	/// Set raycast vector endpoint
	SetLineTraceEndPoint();

	/// Raycast and store in Hit
	World->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEndPoint, TraceObjectParams, TraceCollisionParams);

	/// Debug
	if (ShowDebugInfo)
	{
		DebugInfo();
	}
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Class pressed Grab"), *this->GetName());
}

void UGrabber::SetLineTraceEndPoint()
{
	LineTraceEndPoint = PlayerViewPointLocation + (PlayerViewPointRotation.Vector() * Reach);
}

void UGrabber::DebugInfo()
{
	/// Report the name of the object hit if name different to recent object hit
	if (Hit.GetActor()) {
		if (Hit.GetActor()->GetName() != LastHitActorName)
		{
			LastHitActorName = Hit.GetActor()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%s has been hit by raycast"), *LastHitActorName);
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("Location is: %s and Rotation is: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	DrawDebugLine(World, PlayerViewPointLocation, LineTraceEndPoint, DebugLineColor, false, 0.0f, 0.0f, 10.0f);
}

