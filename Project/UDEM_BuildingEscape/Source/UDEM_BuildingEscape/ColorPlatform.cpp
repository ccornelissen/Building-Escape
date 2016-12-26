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

	// ...
}


// Called when the game starts
void UColorPlatform::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UColorPlatform::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	CheckColor();

	// ...
}

void UColorPlatform::CheckColor()
{
	TArray<AActor*> OverlappingActors;

	if (ColorTrigger == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Attach a color trigger to the color platform"));
		return;
	}

	ColorTrigger->GetOverlappingActors(OverlappingActors);

	for (AActor* CurActor : OverlappingActors)
	{
		if (CurActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("Color platform CurActor is returning null"));
			return;
		}

		UColorTag* ActorColor = CurActor->FindComponentByClass<UColorTag>();

		if (ActorColor == nullptr)
		{
			//Return if the overlapping actor does not have a color tag
			return;
		}

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

	if (OverlappingActors.Num() == 0)
	{
		SetColorCorrect();
	}
	
}

void UColorPlatform::SetColorCorrect()
{
	bColorCorrect = false;
}

