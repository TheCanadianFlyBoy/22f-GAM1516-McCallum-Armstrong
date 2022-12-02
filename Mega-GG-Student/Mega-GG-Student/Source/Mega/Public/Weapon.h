// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupActor.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponFiredSignature);

UCLASS()
class MEGA_API AWeaponActor : public APickupActor
{
	GENERATED_BODY()
#pragma region Region_Private
private:

  
#pragma endregion Region_Private

#pragma region Region_Public
public:
	UPROPERTY(EditDefaultsOnly)
		float FireRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int MaximumAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int CurrentAmmo;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class USoundBase* FireSound;
	/*UPROPERTY(EditDefaultsOnly)
		class UClass* ProjectileType;*/
		/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(BlueprintAssignable)
		FOnWeaponFiredSignature OnWeaponFired;

	// Sets default values for this actor's properties
	AWeaponActor();

	void Equip(class AMegaPlayerPawn* Character);
	void UnEquip();
    
    UFUNCTION()
        void Fire();

	virtual void PullTrigger();
	virtual void ReleaseTrigger();

	FVector GetMuzzleLocation() const;
#pragma endregion Region_Public

#pragma region Region_Protected
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnProjectile();

	FTimerHandle FireTimer;

	//class UPrimitiveComponent* Primitive;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
	    class UArrowComponent* Muzzle;

	void ClearFireTimer();

#pragma endregion Region_Protected
};
