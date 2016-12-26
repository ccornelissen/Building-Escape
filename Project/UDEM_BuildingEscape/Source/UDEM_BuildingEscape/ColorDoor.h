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
	FColorDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FColorDoorEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
	AActor* RedPlatform = nullptr;
	bool bRedSet = false;

	UPROPERTY(EditAnywhere)
	AActor* BluePlatform = nullptr;
	bool bBlueSet = false;

	UPROPERTY(EditAnywhere)
	AActor* YellowPlatform = nullptr;
	bool bYellowSet = false;
};
