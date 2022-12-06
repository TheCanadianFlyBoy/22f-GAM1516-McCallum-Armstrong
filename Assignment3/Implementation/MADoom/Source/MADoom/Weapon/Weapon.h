// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MADOOM_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		class UPaperFlipbook* WeaponFlipbook;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		float Damage;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		 enum class EAmmoType* AmmoType;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		class AProjectile* ProjectileTemplate;

	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void BeginFireTimer();
	void EndFireTimer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
