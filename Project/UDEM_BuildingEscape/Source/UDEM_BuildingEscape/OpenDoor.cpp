// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//TODO move this out of tick, should be able to check when the trigger volume is active

	//Checking if the mass is enough to open the door
	if (GetTotalMassOnPlate() > fMassToOpen)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOnPlate()
{
	float fTotalMass = 0.0f;

	//Actor array set up to hold actors that will have their weight checked
	TArray<AActor*> OverlappingActors;
	
	if (PressurePlate == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Pressure plate not set on %s."), *Owner->GetName());
		return fTotalMass;
	}

	//Getting all the actors in the trigger volume
	PressurePlate->GetOverlappingActors(OverlappingActors);

	//Iterate through and add their masses
	for (AActor* CurActor : OverlappingActors)
	{
		//Access current actors primitive component to get their mass
		if (CurActor == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("CurActor returned a nullptr on GetTotalMassOnPlate()"));
			return fTotalMass;
		}
		
		//Get actors primitive component to check weight
		UPrimitiveComponent* ActPrim = CurActor->FindComponentByClass<UPrimitiveComponent>();

		if (ActPrim != nullptr)
		{
			//Add their mass to the total
			fTotalMass += ActPrim->GetMass();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("CurActor does not have a primitive component attached"));
			return fTotalMass;
		}
	}

	return fTotalMass;
}


