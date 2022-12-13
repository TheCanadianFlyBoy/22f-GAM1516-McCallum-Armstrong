// Fill out your copyright notice in the Description page of Project Settings.

//Enemy
#include "EnemyController.h"
#include "EnemyCharacter.h"
//Components
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
//Nav
#include "NavigationSystem.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
//Player
#include "PlayerCharacter.h"

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Casting check
	if (MyCharacter)
	{
		//Check current state
		switch (MyCharacter->CurrentAIState)
		{
			//Idle wander
			case EAIState::Idle: {
				break;
			}
			//Patrol state
			case EAIState::Patrolling: {
				//Check for patrol routes
				if (MyCharacter->PatrolPoints.Num() > 0)
				{
						MoveToNextPatrolPoint();
				}
				//go to idle if none
				else MyCharacter->CurrentAIState = EAIState::Idle;
				break;
			}
			//Alert state
			case EAIState::Alert: {
				
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "ALERT");
				if (!GetWorldTimerManager().IsTimerActive(SensoryTimerHandle))
				{
					GetWorldTimerManager().SetTimer(SensoryTimerHandle, this, &AEnemyController::PawnAlertTimeOut, 5.f);
				}
				break;
			}
			//Attacking state
			case EAIState::Attacking:{
				//DEBUG
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "ATTACKING");
				//Fire
				if (!GetWorldTimerManager().IsTimerActive(AttackTimerHandle))
				{
					GetWorldTimerManager().SetTimer(AttackTimerHandle, MyCharacter, &AEnemyCharacter::Fire, 2.f);
				}
				break;
			}
		}
	}
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
}

void AEnemyController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	//If possessed is an enemy character type
	if (dynamic_cast<AEnemyCharacter*>(aPawn))
	{
		//Cast
		MyCharacter = dynamic_cast<AEnemyCharacter*>(aPawn);
		//Set patrol point
		if (MyCharacter->PatrolPoints.Num() > 0) CurrentPatrolPoint = (AActor*)MyCharacter->PatrolPoints[0];
		//Set hear/see dynamics
		MyCharacter->PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyController::OnPawnSeen);
		MyCharacter->PawnSensingComponent->OnHearNoise.AddDynamic(this, &AEnemyController::OnNoiseHeard);
	}
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyController::SetupInputComponent()
{
	
}

void AEnemyController::OnPawnSeen(APawn* SeenPawn)
{
	//Check if player
	APlayerCharacter* Player = dynamic_cast<APlayerCharacter*>(SeenPawn);
	if (Player)
	{
		MyCharacter->CurrentAIState = EAIState::Attacking;
		GetWorldTimerManager().SetTimer(SensoryTimerHandle, this, &AEnemyController::PawnAttackTimeOut, 5.f);
		UAIBlueprintHelperLibrary::SimpleMoveToActor(this, Player);
	}
}

void AEnemyController::OnNoiseHeard(APawn* NoiseInstigator, const FVector& Location, float Volume)
{
	APlayerCharacter* Player = dynamic_cast<APlayerCharacter*>(NoiseInstigator);
	if (Player)
	{
		MyCharacter->CurrentAIState = EAIState::Alert;
		GetWorldTimerManager().SetTimer(SensoryTimerHandle, this, &AEnemyController::PawnAlertTimeOut, 5.f);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Location);
	}
}

void AEnemyController::PawnAlertTimeOut()
{
	MyCharacter->CurrentAIState = EAIState::Patrolling;
}

void AEnemyController::PawnAttackTimeOut()
{
	MyCharacter->CurrentAIState = EAIState::Alert;
	if (NavArea)
	{
		NavArea->K2_GetRandomReachablePointInRadius(GetWorld(), GetPawn()->GetActorLocation(),	RandomLocation, 15000.0f);		
		MoveToLocation(RandomLocation);
	}
}

void AEnemyController::MoveToNextPatrolPoint()
{
	//Nav handling
	//Get remaining distance
	float DistanceToNextPoint = (MyCharacter->GetActorLocation() - CurrentPatrolPoint->GetActorLocation()).Size();
	if (DistanceToNextPoint < 100.f)
	{
		//Null catch
		if (CurrentPatrolPoint == nullptr)
		{
			CurrentPatrolPoint = (AActor*)MyCharacter->PatrolPoints[0];
			PatrolPointIndex = 0;
		}
		else
		{
			//Increment index
			PatrolPointIndex++;
			//Traverse
			if (PatrolPointIndex >= MyCharacter->PatrolPoints.Num())
			{
				//Get first point
				CurrentPatrolPoint = (AActor*)MyCharacter->PatrolPoints[0];
				PatrolPointIndex = 0;
			}
			else {
				//Get next point
				CurrentPatrolPoint = (AActor*)MyCharacter->PatrolPoints[PatrolPointIndex];
			}
		}
	}
	//WEEK 10
	//CALL UAIBlueprintHelperLibrary::SimpleMoveToActor() passing in pController, CurrentPatrolPoint
		UAIBlueprintHelperLibrary::SimpleMoveToActor(this, CurrentPatrolPoint);
}
