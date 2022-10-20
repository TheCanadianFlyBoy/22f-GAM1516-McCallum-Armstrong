// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class UE4LAB4_API AProjectile : public AActor
{
	GENERATED_BODY()
	
	/* scene root component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* SceneComponent;

	/* sphere collision component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* SphereComponent;
	
	/** paper sprite component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* ProjectileSprite;

	/* projectile movement component  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
protected:

	// Sets default values for this actor's properties
	AProjectile();

	virtual void BeginPlay() override;

private:	
	/** calls when this actor overlaps another  */
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	

};
