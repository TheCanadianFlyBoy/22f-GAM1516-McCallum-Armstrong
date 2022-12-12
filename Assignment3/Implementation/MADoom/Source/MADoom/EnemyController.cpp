// Fill out your copyright notice in the Description page of Project Settings.

//Enemy
#include "EnemyController.h"
#include "EnemyCharacter.h"
//Components
#include "GameFramework/CharacterMovementComponent.h"
//Nav
#include "NavigationSystem.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"

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

				break;
			}
			//Attacking state
			case EAIState::Attacking:{
				break;
			}
		}
	}
}

void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (MyCharacter) {
		//Set current patrol point
		CurrentPatrolPoint = (AActor*)MyCharacter->PatrolPoints[0];
	}
}

void AEnemyController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (dynamic_cast<AEnemyCharacter*>(aPawn))
	{
		MyCharacter = dynamic_cast<AEnemyCharacter*>(aPawn);
	}
}

void AEnemyController::OnUnPossess()
{
	Super::OnUnPossess();
}

void AEnemyController::SetupInputComponent()
{
	
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
