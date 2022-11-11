// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EInventoryDirection : uint8 {

	NEXT = 0  UMETA(DisplayName = "NEXT"),
	PREV = 1  UMETA(DisplayName = "PREV")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGA_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
#pragma region Region_Private

#pragma endregion Region_Private

#pragma region Region_Public
public:
	// Sets default values for this component's properties
	UInventoryComponent();

	void AddToInventory(class APickupActor* pickup);

	int GetInventoryCount();

	/** 
	* Cycle through the inventory array and equip the next item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual void NextInventoryItem();

	/**
	* Cycle through the inventory array and equip the previous item.
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		virtual void PreviousInventoryItem();

	/**
	* Getter for the currently equipped item.
	* @return Current item
	*/
	UFUNCTION(BlueprintCallable, Category = "Inventory")
		class APickupActor* GetCurrentInventory() const;

	void ResetCurrentInventory();

#pragma endregion Region_Public

#pragma region Region_Protected
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** Item that is currently equipped */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
		class APickupActor* CurrentInventoryItem;

	void EquipNewInventoryItem(APickupActor* NewItem);

	void SelectInventory(EInventoryDirection dir);

public:

	UPROPERTY(VisibleAnywhere)
		TArray< class APickupActor* > Inventory;

#pragma endregion Region_Protected
};
