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
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* aPawn);
	virtual void OnUnPossess();
	virtual void OnDeath();
	virtual void ReloadController();

protected:
	virtual void SetupInputComponent();

	UFUNCTION()
		virtual void OnShot(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageInstigator);

	//Nav System
	class UNavigationSystemV1* NavArea;
	// The current point the actor is either moving to or standing at
	AActor* CurrentPatrolPoint;
	//Patrol point index
	int PatrolPointIndex;

	//Sensory Variables
	FTimerHandle AttackTimerHandle;
	FTimerHandle SensoryTimerHandle;
	//Sensory functions
	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
		void OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume);
	//Timeouts
	UFUNCTION()
		void PawnAlertTimeOut();
	UFUNCTION()
		void PawnAttackTimeOut();


	UFUNCTION() //WIthout this, the function will be inlined and optimized out
		void MoveToNextPatrolPoint();

	//Pointer to enemy character
	class AEnemyCharacter* MyCharacter;
	FVector RandomLocation;
	
};
