// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	//Get pawn
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check if door is closed and if pressure plate is colliding with Player Pawn
	if (CheckPressurePlate() && IsOpen == false) {
		ChangeDoor(GetOpenAngle());
		IsOpen = true;
	}
	else if (!CheckPressurePlate() && IsOpen == true)
	{
		ChangeDoor(GetClosedAngle());
		IsOpen = false;
	}
}


float UOpenDoor::GetOpenAngle()
{
	return OpenAngle;
}

float UOpenDoor::GetClosedAngle()
{
	return ClosedAngle;
}

bool UOpenDoor::CheckPressurePlate()
{
	if (PressurePlate->IsOverlappingActor(Player))
	{
		UE_LOG(LogTemp, Warning, TEXT("WARNING: Collision - IS clipping"));
		return true;
	}
	else
	{
		return false;
	}
}

void UOpenDoor::ChangeDoor(float NewAngle)
{
	//Get the owner of the script (door), create new Rotator object and pass into owner
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f, NewAngle, 0.0f);

	Owner->SetActorRotation(NewRotation);
}