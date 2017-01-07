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

	//Attaching user input to the functions
	void SetUserInput();

	//Setting the physics handle
	void SetPhysicsHandle();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//Checking for hit to trigger rendering highlight
	void HighlightHit(FHitResult LineTraceHit);

private:
	//Player controller reference
	APlayerController* Controller = nullptr;

	//Used to grab what is in reach of the player using raycasting
	void Grab();

	//Used so the player can release objects
	void Release();

	//Player storage vectors
	FVector PlayerLoc;
	FRotator PlayerRot;

	UPROPERTY(EditAnywhere)
	float fPlayerReach = 100.0f; //How far away the player can grab objects

	//Get the the line trace hit
	const FHitResult GetTraceHit();

	//Get the line trace max distance
	const FVector GetLineTraceEnd();

	//Physics handle reference
	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	//Input component reference
	UInputComponent* UserInput = nullptr;
};
