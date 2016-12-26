// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "SimonSaysButton.generated.h"

UENUM()
enum class ESimonColor : uint8
{
	SC_Red,
	SC_Yellow,
	SC_Blue
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API USimonSaysButton : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimonSaysButton();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere)
	ESimonColor SimonColor = ESimonColor::SC_Red;

	UPROPERTY(EditAnywhere)
	AActor* SimonDoor = nullptr;

	void SimonAnswer();
	
};
