// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

UENUM()
	enum class EAIState {
		Idle,
		Patrolling,
		Alert,
		Attacking
	};

UCLASS()
class MADOOM_API AEnemyController : public AAIController
{
	GENERATED_BODY()


public:

	UPROPERTY(VisibleAnywhere, Category = "AI Behaviour")
		EAIState CurrentAIState;

	//TArray<ATargetPoint*>?? TODO

public:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn);
	virtual void OnUnPossess();

protected:
	virtual void SetupInputComponent();

	APawn* MyPawn;
	
};
