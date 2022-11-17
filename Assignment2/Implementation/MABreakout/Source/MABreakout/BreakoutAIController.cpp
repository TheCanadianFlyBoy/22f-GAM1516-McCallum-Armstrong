// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutAIController.h"
#include "PaddlePawn.h"
#include "Ball.h"
#include "EngineUtils.h" //Needed for TActorIterator


ABreakoutAIController::ABreakoutAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Auto shutdown on creation
	bActive = false;

}

void ABreakoutAIController::Tick(float DeltaTime)
{
	
	if (bActive)
	{
		//Create pointer
		ABall* _nearest = nullptr;
		//Iterate all balls
		for (TActorIterator<ABall> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			//find nearest
			if (_nearest == nullptr || LinkedPaddle->GetDistanceTo(*ActorItr) < LinkedPaddle->GetDistanceTo(_nearest))
			{
				_nearest = *ActorItr;
			}
		}

		//Null check
		if (_nearest)
		{
			//Get direction
			float direction = LinkedPaddle->GetHorizontalDistanceTo(_nearest);
			direction /= abs(direction);

			//Move
			LinkedPaddle->MoveRight(direction);

		}

		

	}


}
