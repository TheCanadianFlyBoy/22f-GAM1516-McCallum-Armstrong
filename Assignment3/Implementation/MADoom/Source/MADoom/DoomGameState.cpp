// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomGameState.h"
#include "BackgroundMusicComponent.h"

void ADoomGameState::BeginPlay()
{
	Super::BeginPlay();

	//Set to false
	bLevelComplete = false;
	//Play music
	MusicComponent->Play();
}

ADoomGameState::ADoomGameState() : Super()
{
	MusicComponent = CreateDefaultSubobject<UBackgroundMusicComponent>(TEXT("Music Component"));
}

bool ADoomGameState::IsLevelComplete()
{
	return bLevelComplete;
}
