// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomGameState.h"

void ADoomGameState::BeginPlay()
{
	Super::BeginPlay();

	//Set to false
	bLevelComplete = false;
}

bool ADoomGameState::IsLevelComplete()
{
	return bLevelComplete;
}
