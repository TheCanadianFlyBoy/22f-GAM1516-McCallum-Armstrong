// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MADOOM_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	
	//Player Stats
	UPROPERTY(VisibleAnywhere, Category = "DOOM Character")
		float MaxSpeed;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Chararcter")
		float JumpSpeed;
	UPROPERTY(EditAnywhere, Category = "DOOM Character")
		TSubclassOf<class AWeapon> DefaultWeapon;

	//Components
	UPROPERTY(VisibleAnywhere, Category = "DOOM Character")
		class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Player")
		class UInventoryComponent* InventoryComponent;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Player")
		USceneComponent* WeaponSocket;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Player")
		UPawnNoiseEmitterComponent* NoiseComponent;

	UFUNCTION(BlueprintCallable)
		class AWeapon* GetCurrentWeapon();

	//Pointer to controller
	APlayerController* MyController;


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
	//Interactivity
	void NextWeapon();
	void PreviousWeapon();
	void Interact();
	//Weapons
	void BeginFire();
	void EndFire();
	void Jump();
	//States
	void Die();

private: //Internal variables

	AActor* GetPickableActor_LineTraceSingleByChannel(ECollisionChannel CollisionChannel);

};
