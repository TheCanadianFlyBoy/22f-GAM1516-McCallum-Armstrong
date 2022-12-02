// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GravityWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MEGA_API AGravityWeapon : public AWeaponActor
{
	GENERATED_BODY()

public :

		AGravityWeapon();
		/** Maximum grabbing distance. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float MaxGrabDistance;

		/** Throw velocity. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float ThrowForce;

		/** Threshold in relation to the grabbing distance at which the object is dropped. */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		float DropDistanceThreshold;

		/** Sound to play each time an object is grabbed */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
			class USoundBase* GrabSound;

		/** Sound to play each time an object is thrown */
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
			class USoundBase* ThrowSound;

		/** Physics Handle component */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
			class UPhysicsHandleComponent* PhysicsHandle;

		/** Grab Location component */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
			class USceneComponent* GrabLocation;

		/** Grabbed Mesh component */
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
			class UMeshComponent* GrabbedMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
			bool IsHoldingObject;

		virtual void PullTrigger() override;
		virtual void ReleaseTrigger() override;

	protected:
		/** Update Gravity Gun. */
		void UpdateGravityGun(float DeltaTime);

		/** Handles grab input. */
		void OnGrab();

		/** Handles throwing input. */
		void OnThrow();

		/** Grabs an object. */
		void GrabObject();

		/** Drops the grabbed object. */
		void DropObject();

		/** Throws the grabbed object. */
		void ThrowObject();

		/** Tick character. */
		virtual void Tick(float DeltaTime) override;

		AActor* GrabbedObject;
};
