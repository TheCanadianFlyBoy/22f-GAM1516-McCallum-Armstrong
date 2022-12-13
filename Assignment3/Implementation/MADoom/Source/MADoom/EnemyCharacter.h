// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyController.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MADOOM_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	//Components
	UPROPERTY(EditAnywhere, Category = "DOOM Components")
		class UPaperFlipbookComponent* SpriteComponent;
	UPROPERTY(EditAnywhere, Category = "DOOM Components")
		class UAudioComponent* AudioComponent;

	//Audio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Audio")
		class USoundBase* FireSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Audio")
		class USoundBase* DeathSound;

	//Sprites
	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbook* WalkSprite_Forward;
	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbook* WalkSprite_Left;
	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbook* WalkSprite_Right;
	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbook* DeathSprite_Standard;

	//Stats
	UPROPERTY(VisibleAnywhere, Category = "DOOM Stats")
		float Health;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float MaxHealth;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float MaxSpeed;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float JumpSpeed;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float WeaponDamage;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Accuracy;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		TSubclassOf<class AProjectile> ProjectileTemplate;

	//AI
	UPROPERTY(EditAnywhere, Category = "DOOM AI")
		TArray<class ATargetPoint*> PatrolPoints;
	UPROPERTY(EditAnywhere, Category = "DOOM AI")
		EAIState CurrentAIState;
	UPROPERTY(VisibleAnywhere, Category = "DOOM AI")
		class UPawnSensingComponent* PawnSensingComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnShot(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageInstigator);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement
	void MoveForward(float Value);
	void MoveRight(float Value);
	//Attack
	void Fire();
	//Line Trace
	AActor* GetPickableActor_LineTraceSingleByChannel(ECollisionChannel Channel);
	void SetupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace);
	void SetupTraceParams(FCollisionQueryParams& TraceParams);

};
