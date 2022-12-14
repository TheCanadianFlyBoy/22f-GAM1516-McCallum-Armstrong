// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

UENUM()
enum class EKeyColour {
	Blue,
	Red,
	Yellow
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MADOOM_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	class AWeapon* GetCurrentWeapon();
	AWeapon* NextWeapon();
	AWeapon* PreviousWeapon();
	//Add/pickup
	void AddWeapon(AWeapon* Weapon);
	void PickupWeapon(AWeapon* Weapon);
	void AddKey(EKeyColour Key);
	//Checkers
	bool HasKey(EKeyColour Colour);
	bool HasWeapon(const FName &WeaponName);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	//Internal management of current weapon
	void TraverseInventory(bool right);

	TArray<AWeapon*> Weapons;
	TArray<EKeyColour> Keys;
	AWeapon* CurrentWeapon;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
