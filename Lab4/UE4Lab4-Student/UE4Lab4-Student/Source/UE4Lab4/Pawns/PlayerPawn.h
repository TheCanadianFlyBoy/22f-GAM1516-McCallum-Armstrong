// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UE4Lab4.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"


UCLASS()
class UE4LAB4_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	/*The Characters capsule component, handles collision and is the root component*/
	UPROPERTY(Category = Character, VisibleAnywhere, meta = (AllowPrivateAccess))
		class UCapsuleComponent* CapsuleComponent;

	/*Fire Delay*/
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting")
        float FireTimerDelay = 3;

	/*The Timer Handle for shooting the projectile*/
        FTimerHandle SetCanShootTimer;

	/*Sets bCanShoot allowing character to shoot*/
    UFUNCTION()
        void SetCanShoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UPaperSpriteComponent* PlayerSprite;

	/** camera boom  */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArmComponent;
  
        /** projectile class template  */
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile Blueprint")
        TSubclassOf<class AProjectile> ProjectileTemplate;

	/*Handled Blocking/Hit collision*/
        UFUNCTION()
        virtual void HandleBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

        /** Spawn Projectile if can shoot  */
        UFUNCTION(BlueprintCallable, Category = "Spawn Projectile")
        void SpawnProjectile();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveRight(float value);
	void Jump();
	
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
          class UCameraComponent* FollowCamera;

        bool bCanShoot = false;

private:
        /** projectile spawn point  */
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Projectile", meta = (AllowPrivateAccess = "true"))
        class UArrowComponent* ProjectileSpawnPoint;


        /** returns projectile spawn point **/
        FORCEINLINE class UArrowComponent* GetProjectileSpawnPoint() const { return ProjectileSpawnPoint; }

        /** how much (in sec) player will be inactive after hit  */
        UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
           float ProjectileLifeSpan = 5.f;

	/*Movement Delta*/
	float MovementRight;

	/*Are we on the floor or not*/
	bool bOnFloor;

    //WEEK 10
};
