// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "QuitButton.h"


// Sets default values for this component's properties
UQuitButton::UQuitButton()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UQuitButton::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UQuitButton::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UQuitButton::ExitGame()
{
	PlayQuitSound.Broadcast();
	InitiateQuit.Broadcast();
}

