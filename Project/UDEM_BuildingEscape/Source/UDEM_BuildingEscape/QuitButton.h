// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "QuitButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQuitButtonEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UQuitButton : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UQuitButton();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//Function to call blueprint events
	void ExitGame();

	UPROPERTY(BlueprintAssignable)
	FQuitButtonEvent PlayQuitSound; //Play quit SFX

	UPROPERTY(BlueprintAssignable)
	FQuitButtonEvent InitiateQuit; //Trigger the blueprint to close the game.
	
};
