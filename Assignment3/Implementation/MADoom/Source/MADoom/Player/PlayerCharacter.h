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

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		float speed;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		float MaxSpeed;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		float JumpSpeed;

	UPROPERTY(VisibleAnywhere, Category = "DOOM")
		class UInventoryComponent* InventoryComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float Value);
	void LookRight(float Value);

	void Fire();
	void Jump();

};
