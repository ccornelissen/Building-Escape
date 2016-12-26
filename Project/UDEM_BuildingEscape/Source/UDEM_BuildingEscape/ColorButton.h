// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "ColorButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FColorButtonSoundEvent);

UENUM()
enum class EButtonColor : uint8
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

	UPROPERTY(EditAnywhere)
	EButtonColor ButtonColor = EButtonColor::BC_Red;

	void ChangeColor();

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* ColorTrigger = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* ChangeMaterial;

	UPROPERTY(BlueprintAssignable)
	FColorButtonSoundEvent ColorButtonSuccess;
	UPROPERTY(BlueprintAssignable)
	FColorButtonSoundEvent ColorButtonFail;

	
	
};
