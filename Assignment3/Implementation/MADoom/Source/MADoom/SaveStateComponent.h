// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SaveStateComponent.generated.h"


USTRUCT()
struct FDOOMSaveStateParams {

	GENERATED_BODY()

	FVector Location;
	//State
	float Health;
	float Armour;
	float LightAmmo;
	float MediumAmmo;
	float HeavyAmmo;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MADOOM_API USaveStateComponent : public UActorComponent
{
	GENERATED_BODY()
public:

public:	
	// Sets default values for this component's properties
	USaveStateComponent();

	UPROPERTY(VisibleAnywhere, Category = "DOOM Save")
		FDOOMSaveStateParams CurrentSaveState;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FDOOMSaveStateParams& GetSaveStateParams();
	void SetSaveStateParams(class APlayerCharacter* Character);
		
};
