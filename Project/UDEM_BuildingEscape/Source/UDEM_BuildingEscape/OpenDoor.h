// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen; //Event to tell the door to open

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose; //Event to close the door
	
private:
	UPROPERTY(EditDefaultsOnly)
	float fMassToOpen = 25.0f; //Mass required to open the door

	//Function that gets the total mass of all actors in the trigger
	float GetTotalMassOnPlate();

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr; //Trigger volume that holds actors that need mass checked

	AActor* Owner = nullptr;
};
