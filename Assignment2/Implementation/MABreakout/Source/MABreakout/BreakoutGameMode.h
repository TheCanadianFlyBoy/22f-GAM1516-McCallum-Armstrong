// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BreakoutGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MABREAKOUT_API ABreakoutGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

};
