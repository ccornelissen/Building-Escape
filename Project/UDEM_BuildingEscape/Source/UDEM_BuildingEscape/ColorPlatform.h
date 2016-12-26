// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "ColorPlatform.generated.h"

UENUM()
enum class EColorEnum : uint8
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

	bool bColorCorrect = false;

	UFUNCTION(BlueprintCallable, Category = "ColorPlatform")
	void CheckColor();

	UFUNCTION(BlueprintCallable, Category = "ColorPlatform")
	void SetColorCorrect();

private:
	UPROPERTY(EditAnywhere)
	EColorEnum ColorEnum;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* ColorTrigger = nullptr;
	
};
