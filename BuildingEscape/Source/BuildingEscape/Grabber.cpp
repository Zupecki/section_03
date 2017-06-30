// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


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

	UE_LOG(LogTemp, Warning, TEXT("Grabber is on!"));
	World = GetWorld();

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get the Player Viewpoint - location and rotation - and return them, output results
	World->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	// Set raycast vector endpoint
	FVector LineTraceEndPoint = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Raycast and store in Hit
	World->LineTraceSingleByObjectType(Hit, PlayerViewPointLocation, LineTraceEndPoint, TraceObjectParams, TraceCollisionParams);

	// Debug stuff
	if (Hit.GetActor()) {
		UE_LOG(LogTemp, Warning, TEXT("%s has been hit by raycast"), *(Hit.GetActor()->GetName()));
	}
	//UE_LOG(LogTemp, Warning, TEXT("Location is: %s and Rotation is: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString());
	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEndPoint, DebugLineColor, false, 0.0f, 0.0f, 10.0f);
}

