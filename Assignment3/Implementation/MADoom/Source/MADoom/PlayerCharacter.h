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

	UPROPERTY(EditAnywhere, Category = "DOOM Character Stats")
		float Health = 100.f;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Character")
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Character")
		float speed;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Character")
		float MaxSpeed;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Chararcter")
		float JumpSpeed;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Player")
		class UInventoryComponent* InventoryComponent;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Player")
		USceneComponent* WeaponSocket;




	float WeaponSwayMax;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);
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
	float WeaponSway;
	bool WeaponSwayToggle;

};
