// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DoomGameState.generated.h"

/**
 * 
 */
UCLASS()
class MADOOM_API ADoomGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ADoomGameState();

	bool bLevelComplete;

	UPROPERTY(VisibleAnywhere, Category = "DOOM Music")
		class UBackgroundMusicComponent* MusicComponent;

	UFUNCTION(BlueprintCallable)
		bool IsLevelComplete();

	void CompleteLevel();

protected:
	virtual void BeginPlay() override;
};
