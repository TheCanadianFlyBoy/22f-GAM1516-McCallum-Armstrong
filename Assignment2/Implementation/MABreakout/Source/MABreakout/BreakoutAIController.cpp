// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutAIController.h"
#include "PaddlePawn.h"
#include "Ball.h"
#include "EngineUtils.h" //Needed for TActorIterator


ABreakoutAIController::ABreakoutAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void ABreakoutAIController::Tick(float DeltaTime)
{
	
		//Create pointer
		ABall* _nearest = nullptr;
		//Iterate all balls
		for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			//find nearest
			if (_nearest == nullptr || GetPawn()->GetDistanceTo(*ActorItr) < GetPawn()->GetDistanceTo(_nearest))
			{
				_nearest = *ActorItr;
			}
		}

		//Null check
		if (_nearest && GetPawn())
		{
			//Get location
			FVector displacement = _nearest->GetActorLocation() - GetPawn()->GetActorLocation();

			//Get direction
			float direction = displacement.X;
			direction /= abs(direction);

			//Move
			Cast<APaddlePawn>(GetPawn())->MoveRight(direction);

		}


}
