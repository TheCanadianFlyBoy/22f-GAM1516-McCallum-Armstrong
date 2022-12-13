// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Weapon.h"
#include "DoomPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MADOOM_API ADoomPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	//Ammunition
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float LightAmmo;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float MediumAmmo;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float HeavyAmmo;

	//UFUNCTION(BlueprintCallable)
		float GetAmmo(EAmmoType& Type);


	//Health/Armour
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Health;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Armour;
	UFUNCTION(BlueprintCallable)
		float GetHealth();
	UFUNCTION(BlueprintCallable)
		float GetArmour();

	//Non unreal functions
	void OnDamage(float Damage);
	bool IsDead();

protected:
	virtual void BeginPlay() override;

};
