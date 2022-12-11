// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MADOOM_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(EditAnywhere, Category = "DOOM Sprite")
		class UPaperFlipbookComponent* SpriteComponent;

	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Speed;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float MaxSpeed;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float JumpSpeed;

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
	//Attack
	void Fire();

};
