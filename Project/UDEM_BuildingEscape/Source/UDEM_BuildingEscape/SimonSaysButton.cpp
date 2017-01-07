// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "SimonSaysButton.h"
#include "SimonSaysDoor.h"


// Sets default values for this component's properties
USimonSaysButton::USimonSaysButton()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USimonSaysButton::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void USimonSaysButton::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void USimonSaysButton::SimonAnswer()
{
	if (SimonDoor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s does is missing reference to the simon says door!"), *GetOwner()->GetName());
		return;
	}

	//Getting a reference to the simon door script from the actor
	USimonSaysDoor* SimonSaysDoor = SimonDoor->FindComponentByClass<USimonSaysDoor>();

	if (SimonSaysDoor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Simon says door is missing the SimonSaysDoor script!"));
		return;
	}

	//Answer the simon says script on the simon door based on the buttons state set in the details panel (Default is red)
	if (SimonColor == ESimonColor::SC_Red)
	{
		FString sRed = "Red";
		SimonSaysDoor->AnswerSimon(sRed);
	}
	else if (SimonColor == ESimonColor::SC_Yellow)
	{
		FString sYellow = "Yellow";
		SimonSaysDoor->AnswerSimon(sYellow);
	}
	else if (SimonColor == ESimonColor::SC_Blue)
	{
		FString sBlue = "Blue";
		SimonSaysDoor->AnswerSimon(sBlue);
	}
}

