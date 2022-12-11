// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"
#include "EnemyCharacter.h"

void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Casting check
	if (MyCharacter)
	{
		MyCharacter->AddMovementInput(MyCharacter->GetActorForwardVector());
	}
}

void AEnemyController::BeginPlay()
{
}

void AEnemyController::OnPossess(APawn* aPawn)
{
	if (dynamic_cast<AEnemyCharacter*>(aPawn))
	{
		MyCharacter = dynamic_cast<AEnemyCharacter*>(aPawn);
	}
}

void AEnemyController::OnUnPossess()
{
}

void AEnemyController::SetupInputComponent()
{
}
