// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "UserHighlight.h"


// Sets default values for this component's properties
UUserHighlight::UUserHighlight()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UUserHighlight::BeginPlay()
{
	Super::BeginPlay();

	//Get the static mesh component
	HighlightActor = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
}


// Called every frame
void UUserHighlight::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Revert material if user hasn't looked at it
	if ((GetWorld()->GetTimeSeconds() - fMaterialRevertTimer) > fMaterialRevertTime)
	{
		if (HighlightActor == nullptr)
		{
			return;
		}
		 //Turning off the highlight
		HighlightActor->SetRenderCustomDepth(false);
	}

}

void UUserHighlight::SetMaterial()
{
	if (HighlightActor == nullptr)
	{
		return;
	}

	//Turning on the highlight
	HighlightActor->SetRenderCustomDepth(true);

	//Set the revert timer to current time
	fMaterialRevertTimer = GetWorld()->GetTimeSeconds();
}

