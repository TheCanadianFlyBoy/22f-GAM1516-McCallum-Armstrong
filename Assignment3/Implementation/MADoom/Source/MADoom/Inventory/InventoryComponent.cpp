// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AWeapon* UInventoryComponent::GetCurrentWeapon()
{
	return CurrentWeapon;
}

AWeapon* UInventoryComponent::NextWeapon()
{
	TraverseInventory(true);
	return CurrentWeapon;
}

AWeapon* UInventoryComponent::PreviousWeapon()
{
	TraverseInventory(false);
	return nullptr;
}

bool UInventoryComponent::HasKey(enum class EKeyColour colour)
{
	if (Keys.Find(colour)) return true;
	return false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

//TODO: enum?
void UInventoryComponent::TraverseInventory(bool right)
{
	// Empty catch
	if (Weapons.Num() == 0)
	{
		return;
	}
	//Create empty weapon ptr
	AWeapon* WeaponToEquip = nullptr;
	//Get index
	int32 Index = (right ? 0 : Weapons.Num() - 1);

	//Nullptr check
	if (CurrentWeapon)
	{
		//Find weapon
		Weapons.Find(CurrentWeapon, Index);

		//Determine index
		right ? Index += 1 : Index -= 1;
	}

	//Set new weapon if index is in array
	if (Index < Weapons.Num() && Index > -1)
	{
		CurrentWeapon = Weapons[Index];
	}

	//Call equip function
	//TODO: EQUIP FUNCTION
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

