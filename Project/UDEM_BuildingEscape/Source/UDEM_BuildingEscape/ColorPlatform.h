// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "ColorPlatform.generated.h"

UENUM()
enum class EColorEnum : uint8 //Enum in order to set platform color
{
	CE_Red,
	CE_Yellow,
	CE_Blue
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UColorPlatform : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorPlatform();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//Bool to check if the actor on the platform matches the color criteria 
	bool bColorCorrect = false;

	UFUNCTION(BlueprintCallable, Category = "ColorPlatform")
	void CheckColor(); //Function to check actor color

	UFUNCTION(BlueprintCallable, Category = "ColorPlatform")
	void SetColorCorrectFalse(); //Resets the platforms color correct

private:
	UPROPERTY(EditAnywhere)
	EColorEnum ColorEnum; //Color enum control

	UPROPERTY(EditAnywhere)
	ATriggerVolume* ColorTrigger = nullptr; //Color trigger that will look for actors
	
};
