// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BreakoutAIController.generated.h"

/**
 * 
 */
UCLASS()
class MABREAKOUT_API ABreakoutAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABreakoutAIController();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
