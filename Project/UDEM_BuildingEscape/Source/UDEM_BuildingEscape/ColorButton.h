// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "ColorButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FColorButtonSoundEvent);

UENUM()
enum class EButtonColor : uint8 //Enum to control the color the button represents
{
	BC_Red,
	BC_Yellow,
	BC_Blue
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UColorButton : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorButton();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere) //Needs to be anywhere, so one blueprint can be used for multiple buttons
	EButtonColor ButtonColor = EButtonColor::BC_Red; //Default button color, can be changed on blueprint

	//Function to change color of actors
	void ChangeColor();

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* ColorTrigger = nullptr; //Trigger volume where the actors will sit

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ChangeMaterial; //Material to change the actors to

	UPROPERTY(BlueprintAssignable)
	FColorButtonSoundEvent ColorButtonSuccess; //Success SFX

	UPROPERTY(BlueprintAssignable)
	FColorButtonSoundEvent ColorButtonFail; //Failure SFX

	
	
};
