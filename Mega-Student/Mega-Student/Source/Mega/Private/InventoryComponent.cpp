// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "PickupActor.h"
#include "MegaPlayerPawn.h"
#include "PaperSpriteComponent.h"
//#include "GamePlay1Character.h"
// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::AddToInventory(class APickupActor* pickup)
{
	//CALL AddUnique() on Inventory passing in pickup
	Inventory.AddUnique(pickup);

	//CALL Disable() on pickup
	pickup->Disable();
}

//Week 9 Lab: Select Next Inventory Item
void UInventoryComponent::NextInventoryItem()
{
	//CALL SelectInventory() passing in EInventoryDirection::NEXT
	SelectInventory(EInventoryDirection::NEXT);
}

//Week 9 Lab: Select Previous Inventory Item
void UInventoryComponent::PreviousInventoryItem()
{
	//CALL SelectInventory() passing in EInventoryDirection::PREV
	SelectInventory(EInventoryDirection::PREV);
}

void UInventoryComponent::EquipNewInventoryItem(APickupActor* NewItem)
{
	//IF CurrentInventoryItem IS NOT nullptr
	if (CurrentInventoryItem)
	{
		//CALL Disable() on CurrentInventoryItem
		CurrentInventoryItem->Disable();

		CurrentInventoryItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	}
	//ENDIF

	//IF NewItem IS NOT nullptr
	if (NewItem)
	{
		//CALL Enable() on NewItem
		NewItem->Enable();

		AMegaPlayerPawn* OwningActor = Cast<AMegaPlayerPawn>(GetOwner());
		NewItem->AttachToComponent(OwningActor->PlayerSprite,FAttachmentTransformRules::SnapToTargetIncludingScale, "WeaponSocket");

	}
	//ENDIF

	//SET CurrentInventoryItem to NewItem
	CurrentInventoryItem = NewItem;

}
//Week 9 Lab: This Function Combines the Logic from the Lecture into one function
void UInventoryComponent::SelectInventory(EInventoryDirection dir)
{
	//IF Inventory Num IS 0
	if (Inventory.Num() == 0)
	{
		//RETURN
		return;
	}
	//ENDIF

	//COMMENT: Get the index of the current item and decrement it
	//DECLARE a variable of type APickupActor* called InventoryItemToEquip and SET it to nullptr
	APickupActor* InventoryItemToEquip = nullptr;
	//Use a Ternary Operator to determine the Index https://www.w3schools.com/cpp/cpp_conditions_shorthand.asp
	//UNCOMMENT the line below
	int32 Index = (dir == EInventoryDirection::NEXT ? 0 : Inventory.Num() - 1); // If next, 0, if not, num -1
	//IF CurrentInventoryItem IS NOT nullptr
	if (CurrentInventoryItem)
	{
		//CALL Find() on Inventory passing in CurrentInventoryItem, Index
		Inventory.Find(CurrentInventoryItem, Index);

		//Use a Ternary Operator to determine the Index https://www.w3schools.com/cpp/cpp_conditions_shorthand.asp
		//UNCOMMENT one of the two lines below, they do the same thing
		dir == EInventoryDirection::NEXT ? Index += 1 : Index -= 1;
		//OR
		//Index += (dir == EInventoryDirection::NEXT ?  1 : -1 );
	}
	//ENDIF

	//Set new item when index is inside array
	//IF Index LESS THAN Inventory.Num() AND Index IS GREATER THAN -1  
	if (Index < Inventory.Num() && Index > -1)
		//SET InventoryItemToEquip to Inventory[Index]
		InventoryItemToEquip = Inventory[Index];
	//ENDIF

	//Equip new item
	//CALL EquipNewInventoryItem() passing in InventoryItemToEquip
	EquipNewInventoryItem(InventoryItemToEquip);

}

class APickupActor* UInventoryComponent::GetCurrentInventory() const
{
	return CurrentInventoryItem;
}

void UInventoryComponent::ResetCurrentInventory()
{
	CurrentInventoryItem = nullptr;
}

int UInventoryComponent::GetInventoryCount()
{
	return Inventory.Num();
}

