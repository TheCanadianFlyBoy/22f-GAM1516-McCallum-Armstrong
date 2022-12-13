// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveStateComponent.h"
#include "PlayerCharacter.h"
#include "DoomPlayerState.h"
#include "DoomPlayerController.h"
#include "InventoryComponent.h"

// Sets default values for this component's properties
USaveStateComponent::USaveStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USaveStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USaveStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FDOOMSaveStateParams& USaveStateComponent::GetSaveStateParams()
{
	// // O: insert return statement here
	return CurrentSaveState;
}

void USaveStateComponent::SetSaveStateParams(APlayerCharacter* Character)
{
	ADoomPlayerState* State = (ADoomPlayerState*)Character->GetPlayerState();
	//Location
	CurrentSaveState.Location = Character->GetActorLocation();
	//Save state
	CurrentSaveState.Health = State->Health;
	CurrentSaveState.Armour = State->Armour;
	CurrentSaveState.LightAmmo = State->LightAmmo;
	CurrentSaveState.MediumAmmo = State->MediumAmmo;
	CurrentSaveState.HeavyAmmo = State->HeavyAmmo;
}

