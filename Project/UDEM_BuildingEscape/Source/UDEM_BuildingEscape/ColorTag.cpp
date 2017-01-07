// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "ColorTag.h"


// Sets default values for this component's properties
UColorTag::UColorTag()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UColorTag::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UColorTag::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

