// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// Get Actor name via pointer reference
	FString ObjectName = GetOwner()->GetName();

	// Get Actor position via pointer reference
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();

	// Dereference pointer since otherwise it will print address
	UE_LOG(LogTemp, Warning, TEXT("WARNING: Position Report - %s is at location %s"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

