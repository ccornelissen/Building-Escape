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
	PrimaryComponentTick.bCanEverTick = true;
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
	//Find all overlapping actors
	TArray<AActor*> OverlappingActors;

	if (ColorTrigger == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Color trigger is not set on the button"));
		return;
	}
	ColorTrigger->GetOverlappingActors(OverlappingActors);

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

		UStaticMeshComponent* ActorMesh = CurActor->FindComponentByClass<UStaticMeshComponent>();

		UColorTag* ActorColor = CurActor->FindComponentByClass<UColorTag>();

		if (ActorColor != nullptr)
		{
			if (ActorMesh != nullptr)
			{
				ActorMesh->SetMaterial(0, ChangeMaterial);

				ColorButtonSuccess.Broadcast();
			}

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

