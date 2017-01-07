// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "ColorDoor.h"
#include "ColorPlatform.h"


// Sets default values for this component's properties
UColorDoor::UColorDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UColorDoor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UColorDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//TODO make the platform checks a non-tick function, should only check when the platform state changes. 

	if (RedPlatform != nullptr)
	{
		bRedSet = RedPlatform->FindComponentByClass<UColorPlatform>()->bColorCorrect; //Checking if the red platform has the correct actor
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No red platform set on the color door!"))
	}

	if (YellowPlatform != nullptr)
	{
		bYellowSet = YellowPlatform->FindComponentByClass<UColorPlatform>()->bColorCorrect; //Yellow platform check
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No yellow platform set on the color door!"))
	}

	if (BluePlatform != nullptr)
	{
		bBlueSet = BluePlatform->FindComponentByClass<UColorPlatform>()->bColorCorrect; //Blue platform check
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No blue platform set on the color door!"))
	}
	

	if (bRedSet == true && bBlueSet == true && bYellowSet == true)
	{
		OnOpen.Broadcast(); //If all platforms are correctly set open the door
	}
	else
	{
		OnClose.Broadcast();
	}
}

