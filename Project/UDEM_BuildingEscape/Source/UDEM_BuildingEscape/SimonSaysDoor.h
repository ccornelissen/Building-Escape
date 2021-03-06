// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "SimonSaysDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimonDoorEvent);

UENUM()
enum class EPanelPhase : uint8 //Enum to control the state of the simon says game
{
	PP_Phase1,
	PP_Phase2,
	PP_Phase3,
	PP_Phase4
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API USimonSaysDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimonSaysDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere)
	AActor* SimonPanel = nullptr; //Reference to the simon panel, this is what displays the colors the player needs to answer to

	//Functions for resetting the sequence or moving the player up to the next level upon completion.
	void SequenceSuccess();
	void SequenceReset();

	//Public function for the player to relay button input to this script
	void AnswerSimon(FString sAnswer);

	//Checking if the array has be completed correctly.
	void ArrayCorrect();

	//Blueprint function to open door when player wins
	UPROPERTY(BlueprintAssignable)
	FSimonDoorEvent DoorOpen;

	//Blueprint function to trigger the success SFX, when player hits the right button
	UPROPERTY(BlueprintAssignable)
	FSimonDoorEvent DoorSuccess;

	//Blueprint function to trigger the fail SFX, when player hits the wrong button
	UPROPERTY(BlueprintAssignable)
	FSimonDoorEvent DoorFail;
	
private:

	//Enum which controls which phase of the game the player is in, higher phase number increased difficulty
	EPanelPhase PanelPhase = EPanelPhase::PP_Phase1;

	//Array that holds the simon says game's sequence of colors
	TArray<FString> SimonArray;

	//Variables to handle when the panel will switch colors
	UPROPERTY(EditAnywhere)
	float fPanelChangeTimer = 1.5f;

	//Variables that control when the color should change, and what color to change too.
	float fTimer = 0.0f;
	int32 iArrayLength = 0;
	bool bToggleChange = false;

	//Reference to simon panel for color changing
	UStaticMeshComponent* SimonPanelMesh = nullptr;

	//Function that controls the sequence the panel goes through based on the phase enum
	void SimonPanelColorSequence();

	//Function that loops the panel through the colors in the sequence.
	void PanelColorLoop();

	//Private color variables
	FString sRed = "Red";
	FString sBlue = "Blue";
	FString sYellow = "Yellow";
	FString sBlack = "Black";

	//References to the various colors the panel can change to.
	UPROPERTY(EditAnywhere)
	UMaterialInterface* RedMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BlueMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* YellowMaterial;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BlackMaterial; //Reset color, player does not have access to this button, it is where the sequence restarts
};
