// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BreakoutGameState.generated.h"

/**
 * 
 */
UCLASS()
class MABREAKOUT_API ABreakoutGameState : public AGameStateBase
{
	GENERATED_BODY()

	public:
		//Constructor
		ABreakoutGameState();

		UFUNCTION(BlueprintCallable)
			int GetScore();
		UFUNCTION(BlueprintCallable)
			int GetLives();
		UFUNCTION(BlueprintCallable)
			void DefeatPlayer();

		float totalScore;
		bool bDefeat;
		int lives;
	
};
