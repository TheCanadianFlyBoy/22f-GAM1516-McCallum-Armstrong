// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "Weapon.h"
#include "InventoryComponent.h"
#include "Pickup.generated.h"

UENUM()
enum class EPickupType {
	Weapon,
	Ammo,
	Health,
	Armour,
	Key
};

UCLASS()
class MADOOM_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

	//Components
	UPROPERTY(EditAnywhere, Category = "Pickup")
		class UPaperFlipbookComponent* SpriteComponent;
	UPROPERTY(EditAnywhere, Category = "Pickup")
		class USphereComponent* PickupSphere;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Audio")
		class USoundBase* PickupSound;

	//Backend Properties
	UPROPERTY(EditAnywhere, Category = "DOOM")
		EPickupType PickupType;
	UPROPERTY(EditAnywhere, Category = "DOOM")
		EAmmoType AmmoType;
	UPROPERTY(EditAnywhere, Category = "DOOM")
		TSubclassOf<class AWeapon> WeaponTemplate;
	UPROPERTY(EditAnywhere, Category = "DOOM")
		float PickupValue;
	UPROPERTY(EditAnywhere, Category = "DOOM")
		EKeyColour KeyColour;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
