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

		//Lives Getter
		UFUNCTION(BlueprintCallable)
			int GetLives();
		//Victory/Defeat Calls
		UFUNCTION(BlueprintCallable)
			void Defeat();
		UFUNCTION(BlueprintCallable)
			void Victory();
		//Victory/Defeat checkers
		UFUNCTION(BlueprintCallable)
			bool IsDefeated();
		UFUNCTION(BlueprintCallable)
			bool IsVictorious();
		//Sounds
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
			class USoundBase* DefeatSound;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
			class USoundBase* VictorySound;
		//Data for storage
		bool bDefeat;
		bool bVictory;
		int lives;
	
};
