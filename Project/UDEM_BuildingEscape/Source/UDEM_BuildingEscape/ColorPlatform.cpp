// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "ColorPlatform.h"
#include "ColorTag.h"


// Sets default values for this component's properties
UColorPlatform::UColorPlatform()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UColorPlatform::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UColorPlatform::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	
	//TODO move this out of tick, should be able to check when the trigger contains overlaps
	CheckColor();
}

//Function to check the colors of the actors
void UColorPlatform::CheckColor()
{
	//Setting up array to hold actors.
	TArray<AActor*> OverlappingActors;

	if (ColorTrigger == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Attach a color trigger to the color platform"));
		return;
	}

	//Putting any overlapping actors in the array
	ColorTrigger->GetOverlappingActors(OverlappingActors);

	//Loop through the actors in the array
	for (AActor* CurActor : OverlappingActors)
	{
		if (CurActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Color platform CurActor is returning null"));
			return;
		}

		//Get the actors color tag
		UColorTag* ActorColor = CurActor->FindComponentByClass<UColorTag>();

		if (ActorColor == nullptr)
		{
			//Return if the overlapping actor does not have a color tag
			return;
		}

		//Check if actors color tag matches the platform color tag. 
		if (ColorEnum == EColorEnum::CE_Red)
		{
			if (ActorColor->RockColor == ERockColor::RC_Red)
			{
				bColorCorrect = true;
			}
		}
		else if (ColorEnum == EColorEnum::CE_Blue)
		{
			if (ActorColor->RockColor == ERockColor::RC_Blue)
			{
				bColorCorrect = true;
			}
		}
		else if (ColorEnum == EColorEnum::CE_Yellow)
		{
			if (ActorColor->RockColor == ERockColor::RC_Yellow)
			{
				bColorCorrect = true;
			}
		}
	}

	//If no actors are overlapping set false
	if (OverlappingActors.Num() == 0)
	{
		SetColorCorrectFalse();
	}
	
}

//Simply resets the bool back to false
void UColorPlatform::SetColorCorrectFalse()
{
	bColorCorrect = false;
}

