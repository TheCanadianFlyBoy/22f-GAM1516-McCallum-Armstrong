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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile Movement")
        class UProjectileMovementComponent* ProjectileMovementComponent;

protected:

    virtual void BeginPlay() override;

    //Week 9 Lab: Set In Editor
    UPROPERTY(EditDefaultsOnly, Category = "Effects")
        UParticleSystem* ProjectileFX;

    //Week 9 Lab: Set In Editor
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
        class USoundBase* ImpactSound;

    //Week 9 Lab: Set In Editor for Different projectile types
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int MaximumSpeed = 20000;

    //Week 9 Lab: Set In Editor for Different projectile types
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int InitialSpeed = 5000;

    //Week 9 Lab: Optional, Use Components for sound
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
    //    class UAudioComponent* AudioComponent;

    //Week 9 Lab: Optional, Use Component for particles
    //UPROPERTY(VisibleAnywhere)
    //    class UParticleSystemComponent* PSC; //THis is a scene component, and can be attached to actors
    
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class USceneComponent* SceneComponent;

    /* sphere collision component  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class USphereComponent* SphereComponent;

    /** paper sprite component  */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
        class UPaperSpriteComponent* ProjectileSprite;

    /** calls when this actor overlaps another  */
    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
