// Copyright Cody Cornelissen 2016.

#include "UDEM_BuildingEscape.h"
#include "SimonSaysDoor.h"


// Sets default values for this component's properties
USimonSaysDoor::USimonSaysDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USimonSaysDoor::BeginPlay()
{
	Super::BeginPlay();

	if (SimonPanel != nullptr)
	{
		//Get reference to the simonpanels mesh to change its color
		SimonPanelMesh = SimonPanel->FindComponentByClass<UStaticMeshComponent>();
	}

	//Set the sequence to the beginning (just for safety)
	SequenceReset();
}


// Called every frame
void USimonSaysDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float fWorldTime = GetWorld()->TimeSeconds;

	//Checks if the array is empty
	if (SimonArray.Num() != 0)
	{
		//If the current element exists within the array allow color change.
		if (iArrayLength < SimonArray.Num())
		{
			if ((fTimer > fWorldTime) && bToggleChange == true) //If the timer allows and a color change is possible
			{
				SimonPanelColorSequence();
				bToggleChange = false;

			}
			else if(fTimer < fWorldTime) //Reset the timer and toggle upon the timer running out
			{
				fTimer = fWorldTime + fPanelChangeTimer;
				bToggleChange = true;
			}
		}
		else //Reset the array to restart the loop
		{
			iArrayLength = 0;
		}
	}
}

//Called when the player finishes the simon sequence to move them up or open the door.
void USimonSaysDoor::SequenceSuccess()
{
	if (PanelPhase == EPanelPhase::PP_Phase1)
	{
		PanelPhase = EPanelPhase::PP_Phase2; //Set to next phase
		SequenceReset(); //reset seqeunce
		iArrayLength = 0; //Reset the array length
	}
	else if (PanelPhase == EPanelPhase::PP_Phase2)
	{
		PanelPhase = EPanelPhase::PP_Phase3;
		SequenceReset();
		iArrayLength = 0;
	}
	else if (PanelPhase == EPanelPhase::PP_Phase3)
	{
		PanelPhase = EPanelPhase::PP_Phase4;
		SequenceReset();
		iArrayLength = 0;
		SequenceSuccess();
	}
	else if (PanelPhase == EPanelPhase::PP_Phase4)
	{
		DoorOpen.Broadcast();
		iArrayLength = 0;
	}
}

//Used to reset the array back to its origin, and add all the strings back. 
void USimonSaysDoor::SequenceReset()
{
	if (PanelPhase == EPanelPhase::PP_Phase1)
	{
		if (SimonArray.Num() != 0)
		{
			SimonArray.Empty();
		}

		//The emplace list below is what controls what colors are in the seqeunce
		SimonArray.Emplace(sBlack); //A black panel must always come first so the player knows where the sequence resets
		SimonArray.Emplace(sRed);
		SimonArray.Emplace(sYellow);
	}
	else if (PanelPhase == EPanelPhase::PP_Phase2)
	{
		if (SimonArray.Num() != 0)
		{
			SimonArray.Empty();
		}

		SimonArray.Emplace(sBlack);
		SimonArray.Emplace(sRed);
		SimonArray.Emplace(sYellow);
		SimonArray.Emplace(sBlue);
		SimonArray.Emplace(sYellow);
	}
	else if (PanelPhase == EPanelPhase::PP_Phase3)
	{
		if (SimonArray.Num() != 0)
		{
			SimonArray.Empty();
		}

		SimonArray.Emplace(sBlack);
		SimonArray.Emplace(sBlue);
		SimonArray.Emplace(sRed);
		SimonArray.Emplace(sYellow);
		SimonArray.Emplace(sBlue);
		SimonArray.Emplace(sRed);
	}
	else if (PanelPhase == EPanelPhase::PP_Phase4)
	{
		if (SimonArray.Num() != 0)
		{
			SimonArray.Empty();
		}
	}
}

//Taking the answer based on the button pushed in the world and relaying it to the door.
void USimonSaysDoor::AnswerSimon(FString sAnswer)
{
	//Checking if the array is empty
	if (SimonArray.Num() != 0)
	{
		//Check what the answer is
		if (sAnswer == sRed)
		{
			//If the answer matches the second string in the sequence, first is always black so the user knows where the sequence resets.
			if (SimonArray[1] == sRed)
			{
				DoorSuccess.Broadcast();
				ArrayCorrect();
			}
			else //Reset the sequence as it was incorrect. 
			{
				DoorFail.Broadcast();
				SequenceReset();
			}
		}
		else if (sAnswer == sYellow)
		{
			if (SimonArray[1] == sYellow)
			{
				DoorSuccess.Broadcast();
				ArrayCorrect();
			}
			else
			{
				DoorFail.Broadcast();
				SequenceReset();
			}
		}
		else if (sAnswer == sBlue)
		{
			if (SimonArray[1] == sBlue)
			{
				DoorSuccess.Broadcast();
				ArrayCorrect();
			}
			else
			{
				DoorFail.Broadcast();
				SequenceReset();
			}
		}
	}
}

//A function used to remove the current top item from the array. 
void USimonSaysDoor::ArrayCorrect()
{
	//Remove one from the array so the user no longer has to answer.
	SimonArray.RemoveAt(1);

	if (SimonArray.Num() == 1) //If down to 1 in the array (only the black panel) move onto next phase
	{
		SequenceSuccess();
	}
}

//Used to control the color swapping of the panel. 
void USimonSaysDoor::SimonPanelColorSequence()
{
	if (PanelPhase == EPanelPhase::PP_Phase1)
	{
		PanelColorLoop();
	}
	else if (PanelPhase == EPanelPhase::PP_Phase2)
	{
		PanelColorLoop();
	}
	else if (PanelPhase == EPanelPhase::PP_Phase3)
	{
		PanelColorLoop();
	}
	else if (PanelPhase == EPanelPhase::PP_Phase4)
	{
		SimonPanelMesh->SetMaterial(0, BlackMaterial);
	}
}

//Sets the color of the panel based on the strings set in the array.
void USimonSaysDoor::PanelColorLoop()
{
	if (SimonArray[iArrayLength] == sRed)
	{
		if (SimonPanelMesh != nullptr)
		{
			SimonPanelMesh->SetMaterial(0, RedMaterial); //Changing the panels material color
			iArrayLength++;
		}
	}
	else if (SimonArray[iArrayLength] == sYellow)
	{
		if (SimonPanelMesh != nullptr)
		{
			SimonPanelMesh->SetMaterial(0, YellowMaterial);
			iArrayLength++;
		}
	}
	else if (SimonArray[iArrayLength] == sBlue)
	{
		if (SimonPanelMesh != nullptr)
		{
			SimonPanelMesh->SetMaterial(0, BlueMaterial);
			iArrayLength++;
		}
	}
	else if (SimonArray[iArrayLength] == sBlack)
	{
		if (SimonPanelMesh != nullptr)
		{
			SimonPanelMesh->SetMaterial(0, BlackMaterial);
			iArrayLength++;
		}
	}
}

