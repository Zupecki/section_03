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

	//Get pointers to necessary objects
	Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	Owner = GetOwner();
	World = GetWorld();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check if door is closed and if pressure plate is colliding with Player Pawn
	if (CheckPressurePlate() && IsOpen == false) {
		ChangeDoor(GetOpenAngle());
	}

	//If door is already open and player is on PressurePlate (maybe they came back while it was still open), keep resetting timer
	if (CheckPressurePlate() && IsOpen == true) {
		SetDoorChangeTime(World->GetTimeSeconds());
	}

	//Check of door is open and pressure plate isn't being stood on - then start timer to close door
	if (!CheckPressurePlate() && IsOpen == true)
	{
		//If time player left pressure plate hasn't been set, set it
		if (TimerSettable == true) {
			SetDoorChangeTime(World->GetTimeSeconds());
		}
		
		//Check if the amount of delay time has passed, close door
		if (TimerSettable == false && DelayTimer())
		{
			ChangeDoor(GetClosedAngle());
		}
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

void UOpenDoor::SetDoorChangeTime(float Seconds)
{
	//Set timer, lock it to prevent ticker constantly updating
	DoorChangeTime = Seconds;
	TimerSettable = false;
}

bool UOpenDoor::CheckPressurePlate()
{
	if (PressurePlate->IsOverlappingActor(Player))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UOpenDoor::DelayTimer()
{
	//Set timer begin time
	float CurrentTime = World->GetTimeSeconds();
	//float Timer = CurrentTime - DoorChangeTime;

	//FString TimeCount = FString::SanitizeFloat(Timer);

	//UE_LOG(LogTemp, Warning, TEXT("Timer: %s"), TimeCount);

	//If a set amount of time has passed since no pressure on PressurePad
	if (CurrentTime - DoorChangeTime >= DoorTimer)
	{
		return true;
	}

	return false;
}

void UOpenDoor::ChangeDoor(float NewAngle)
{
	//Set new rotation angle for Owner asset
	Owner->SetActorRotation(FRotator(0.0f, NewAngle, 0.0f));
	
	//Set door state and open timer settable
	if (IsOpen == false)
	{
		IsOpen = true;
		TimerSettable = true;
	}
	else {
		IsOpen = false;
	}
}