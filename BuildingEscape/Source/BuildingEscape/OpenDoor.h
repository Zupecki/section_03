// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetOpenAngle();
	float GetClosedAngle();
	bool CheckPressurePlate();
	void ChangeDoor(float NewAngle);
	void SetDoorTimer(float Seconds);

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 0.0f;

	UPROPERTY(EditAnywhere)
	float ClosedAngle = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	AActor* Owner;
	AActor* Player;
	UWorld* World;

	float DoorChangeTime = 0.0f;
	bool IsOpen = false;
};
