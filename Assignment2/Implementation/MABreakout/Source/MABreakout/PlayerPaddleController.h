// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerPaddleController.generated.h"

/**
 * 
 */
UCLASS()
class MABREAKOUT_API APlayerPaddleController : public APlayerController
{
	GENERATED_BODY()
public:
	//Begin Play Override - set camera
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

protected:
	//Setup
	virtual void SetupInputComponent() override;

	virtual void AcknowledgePossession(APawn* PossesedPawn) override;


	//Movement for axis
	void MoveRight(float _value);

	class APaddlePawn* MyPawn;
	class ABoard* MyBoard;

};
