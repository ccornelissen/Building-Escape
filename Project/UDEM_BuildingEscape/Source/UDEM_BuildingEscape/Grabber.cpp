// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "Grabber.h"
#include "UserHighlight.h"
#include "ColorButton.h"
#include "SimonSaysButton.h"
#include "QuitButton.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Get player controller
	Controller = GetWorld()->GetFirstPlayerController();

	SetPhysicsHandle();

	SetUserInput();
}

// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	//Check if the player is looking at an interactable object
	HighlightHit(GetTraceHit());

	//If physics handle is attached
	if (PhysicsHandle == nullptr)
	{
		return; //nullptr check
	}

	//Check if the player is holding an object
	if (PhysicsHandle->GrabbedComponent)
	{
		FVector TraceEnd = GetLineTraceEnd();
		//Move object we're holding
		PhysicsHandle->SetTargetLocation(TraceEnd);
	}

}

//Attaching user input to the functions
void UGrabber::SetUserInput()
{
	//Getting the users input component and error checking
	UserInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (UserInput != nullptr)
	{
		//Bind Input Axis
		UserInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		UserInput->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		FString sThisPawn = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s IS LACKING AN INPUT COMPONENT!"), *sThisPawn);
	}
}

//Checking if the player has a physics handle and setting the variable
void UGrabber::SetPhysicsHandle()
{
	//Find attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		FString sThisPawn = GetOwner()->GetName();
		UE_LOG(LogTemp, Error, TEXT("%s IS LACKING A PHYSICS HANDLE!"), *sThisPawn);
	}
}

//Turning on the post process of the actor to give it the highlight
void UGrabber::HighlightHit(FHitResult LineTraceHit)
{
	if (LineTraceHit.Actor != nullptr)
	{
		//Get the UUserhighlight component from the actor
		UUserHighlight* ActorHighlight = LineTraceHit.Actor->FindComponentByClass<UUserHighlight>();

		//Check to make sure the actor has the component
		if (ActorHighlight != nullptr)
		{
			//Turning on the post process
			ActorHighlight->SetMaterial();
		}
	}
}

void UGrabber::Grab()
{
	//Line Trace Try and reach any actors with correct collision
	FHitResult HitResult = GetTraceHit();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();

	//If we hit something attach it to the physics handle
	if (ActorHit != nullptr)
	{
		if (ActorHit->ActorHasTag("InteractRock")) //If it is an interact rock attach the object to the physics handle
		{
			PhysicsHandle->GrabComponent
				(
					ComponentToGrab,
					NAME_None,
					ComponentToGrab->GetOwner()->GetActorLocation(),
					true //Allows rotation
				);
		}
		else if (ActorHit->ActorHasTag("ColorButton")) //If it is the color button, trigger the change color script on the button.
		{
			UColorButton* ColorButton = ActorHit->FindComponentByClass<UColorButton>();

			if (ColorButton != nullptr)
			{
				ColorButton->ChangeColor();
			}
		}
		else if (ActorHit->ActorHasTag("SimonSaysButton")) //If it is the simon says button enter the answer
		{
			USimonSaysButton* SimonButton = ActorHit->FindComponentByClass<USimonSaysButton>();

			if (SimonButton != nullptr)
			{
				SimonButton->SimonAnswer();
			}
		}
		else if (ActorHit->ActorHasTag("QuitButton")) //If it is the quit button quit the game
		{
			UQuitButton* QuitButton = ActorHit->FindComponentByClass<UQuitButton>();

			if (QuitButton != nullptr)
			{
				QuitButton->ExitGame();
			}
		}
	}
}

//Function that detaches the current held object on the physics handle
void UGrabber::Release()
{
	if (PhysicsHandle == nullptr)
	{
		return; //nullptr check
	}
	PhysicsHandle->ReleaseComponent();
}

//Getting the line trace hit
const FHitResult UGrabber::GetTraceHit()
{
	//Get the end vector of the trace
	FVector GrabberTraceEnd = GetLineTraceEnd();

	FHitResult LineTraceHit;

	//Set up query params
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	//Performing a line trace that will only return if hitting a physics object
	GetWorld()->LineTraceSingleByObjectType
		(
			LineTraceHit,
			PlayerLoc,
			GrabberTraceEnd,
			FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
			TraceParams
		);

	if (LineTraceHit.Actor != nullptr)
	{
		return LineTraceHit;
	}

	return LineTraceHit;
}

//Getting the max length of the line trace
const FVector UGrabber::GetLineTraceEnd()
{
	Controller->GetPlayerViewPoint(PlayerLoc, PlayerRot);

	FVector LineTraceEnd = PlayerLoc + (PlayerRot.Vector() * fPlayerReach);

	return LineTraceEnd;
}

