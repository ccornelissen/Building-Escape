// Copyright Cody Cornelissen 2016

#pragma once

#include "Components/ActorComponent.h"
#include "ColorDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FColorDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UColorDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UColorDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FColorDoorEvent OnOpen; //Blueprint event to trigger the opening of the door

	UPROPERTY(BlueprintAssignable)
	FColorDoorEvent OnClose; //Blueprint event to trigger the closing of the door

private:
	UPROPERTY(EditAnywhere)
	AActor* RedPlatform = nullptr; //Red platform actor reference
	bool bRedSet = false; //Bool to check if red platform has a red rock on it 

	UPROPERTY(EditAnywhere)
	AActor* BluePlatform = nullptr; //Blue platform actor reference 
	bool bBlueSet = false; //Blue bool check

	UPROPERTY(EditAnywhere)
	AActor* YellowPlatform = nullptr; //Yellow platform
	bool bYellowSet = false; //Yellow bool check
};
