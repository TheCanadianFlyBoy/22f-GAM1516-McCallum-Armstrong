// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Projectile.generated.h"

/**
 * 
 */
UCLASS()
class MEGA_API AProjectile : public AActor
{
	GENERATED_BODY()
	
   
public:
    // Sets default values for this actor's properties
    AProjectile();

    void SetFireDirection(FVector dir);
    /* projectile movement component  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
        class UProjectileMovementComponent* ProjectileMovementComponent;

protected:

    virtual void BeginPlay() override;

    //Week 11
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
        UParticleSystem* ProjectileFX;

    //UPROPERTY(VisibleAnywhere)
    //    class UParticleSystemComponent* PSC; //THis is a scene component, and can be attached to actors

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int MaximumSpeed = 20000;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int InitialSpeed = 5000;

    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
    //    class UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class USoundBase* ImpactSound;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class USceneComponent* SceneComponent;

    /* sphere collision component  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class USphereComponent* SphereComponent;

    /** paper flipbook component  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* ProjectileSprite;

    /** calls when this actor overlaps another  */
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
