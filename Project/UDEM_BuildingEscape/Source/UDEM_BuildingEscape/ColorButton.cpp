// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "ColorButton.h"
#include "ColorTag.h"


// Sets default values for this component's properties
UColorButton::UColorButton()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UColorButton::BeginPlay()
{
	Super::BeginPlay();
}

void UColorButton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
}

void UColorButton::ChangeColor()
{
	//Creating an array to hold any overlapping actors
	TArray<AActor*> OverlappingActors;

	if (ColorTrigger == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Color trigger is not set on the button"));
		return;
	}

	//Adding overlapping actors to the array
	ColorTrigger->GetOverlappingActors(OverlappingActors);

	//Play fail SFX if player hits the button but nothing is on the platform.
	if (OverlappingActors.Num() == 0)
	{
		ColorButtonFail.Broadcast();
	}

	//Iterate through and add their masses
	for (AActor* CurActor : OverlappingActors)
	{
		//Access current actors primitive component to get their mass
		if (CurActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("CurActor returned a nullptr on GetTotalMassOnPlate()"));
		}

		//Getting static mesh component.
		UStaticMeshComponent* ActorMesh = CurActor->FindComponentByClass<UStaticMeshComponent>();

		//Checking set color of the actor
		UColorTag* ActorColor = CurActor->FindComponentByClass<UColorTag>();

		if (ActorColor != nullptr)
		{
			if (ActorMesh != nullptr)
			{
				//Setting the material color of the actors
				ActorMesh->SetMaterial(0, ChangeMaterial);

				//Play success SFX to the player
				ColorButtonSuccess.Broadcast();
			}

			//Set the actor enum color based on pressed button color
			if (ButtonColor == EButtonColor::BC_Red)
			{
				ActorColor->RockColor = ERockColor::RC_Red;
			}
			else if (ButtonColor == EButtonColor::BC_Yellow)
			{
				ActorColor->RockColor = ERockColor::RC_Yellow;
			}
			else
			{
				ActorColor->RockColor = ERockColor::RC_Blue;
			}
		}
		
	}


}

