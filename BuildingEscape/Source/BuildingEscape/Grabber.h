// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DebugInfo();
	void SetLineTraceEndPoint();
	void Grab();
	void GetRequiredObjects();

private:
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	FVector LineTraceEndPoint;
	UWorld* World;
	FHitResult Hit;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input;
	FString LastHitActorName = "";
	
	//Query Parameters - No name, simple colliders, ignore pawn, hit physicsbody
	FCollisionQueryParams TraceCollisionParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
	FCollisionObjectQueryParams TraceObjectParams = FCollisionObjectQueryParams(ECollisionChannel(ECollisionChannel::ECC_PhysicsBody));

	UPROPERTY(EditAnywhere)
	float Reach = 150.0f;

	UPROPERTY(EditAnywhere)
	FColor DebugLineColor = FColor(255.0f, 0.0f, 0.0f, 0.0f);

	UPROPERTY(EditAnywhere)
	bool ShowDebugInfo = false;
};
