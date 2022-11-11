// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class MEGA_API AAmmoPickup : public APickupActor
{
	GENERATED_BODY()
	
public :
    AAmmoPickup();
    UPROPERTY(EditDefaultsOnly, Category = AmmoCount)
        uint32 AmmoCount;
			
};
