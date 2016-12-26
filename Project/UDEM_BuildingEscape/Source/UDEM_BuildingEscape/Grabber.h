// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;

	void SetUserInput();

	void SetPhysicsHandle();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void HighlightHit(FHitResult LineTraceHit);

private:
	APlayerController* Controller;

	//Used to grab what is in reach of the player using raycasting
	void Grab();

	//Used so the player can release objects
	void Release();

	FVector PlayerLoc;
	FRotator PlayerRot;

	UPROPERTY(EditAnywhere)
	float fPlayerReach = 100.0f;

	const FHitResult GetTraceHit();

	const FVector GetLineTraceEnd();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* UserInput = nullptr;
	
};
