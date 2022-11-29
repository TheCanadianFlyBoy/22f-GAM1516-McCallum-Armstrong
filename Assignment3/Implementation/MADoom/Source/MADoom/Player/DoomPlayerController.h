// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DoomPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MADOOM_API ADoomPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	//virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

protected:
	//Setup
	virtual void SetupInputComponent() override;

	void Exit();

	//Movement for axis
	//void MoveRight(float _value);
	//void MoveForward(float _value)

	class APlayerCharacter* MyPawn;

};
