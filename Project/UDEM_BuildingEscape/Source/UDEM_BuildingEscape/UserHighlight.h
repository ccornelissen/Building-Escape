// Copyright Cody Cornelissen 2016.

#pragma once

#include "Components/ActorComponent.h"
#include "UserHighlight.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEM_BUILDINGESCAPE_API UUserHighlight : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUserHighlight();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	//Function used to turn on custom depth to show outline
	void SetMaterial();

private:
	//Reference to the highlight actor
	UStaticMeshComponent* HighlightActor = nullptr;

	//Timer used to turn off the highlight when player leaves it
	float fMaterialRevertTimer;

	//How long before the highlight turns off
	UPROPERTY(EditAnywhere)
	float fMaterialRevertTime = 0.2f;
	
};
