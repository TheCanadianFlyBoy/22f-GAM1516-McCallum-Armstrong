// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class MEGA_API AWeaponActor : public APickupActor
{
	GENERATED_BODY()
#pragma region Region_Private
private:

  
#pragma endregion Region_Private

#pragma region Region_Public
public:

	UPROPERTY(EditAnywhere, Category = "Custom")
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gunion Rings")
		int MaximumAmmo;

	UPROPERTY(EditAnywhere, Category = "Gunion Rings")
		int CurrentAmmo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
        class UAudioComponent* AudioComponent;

	//Week 9 Lab: Set In Editor
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom")
        class USoundBase* FireSound;

	//Week 9 Lab: Set In Editor
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UArrowComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		FTimerHandle FireRateTimer;

	// Sets default values for this actor's properties
	AWeaponActor();

	void Equip(class AMegaPlayerPawn* Character);
	void UnEquip();
    
    UFUNCTION()
        void Fire();
	UFUNCTION()
		void StartFire();
	UFUNCTION()
		void EndFire();

	FVector GetMuzzleLocation() const;

#pragma endregion Region_Public

#pragma region Region_Protected
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SpawnProjectile();

	//Timer

#pragma endregion Region_Protected
};
