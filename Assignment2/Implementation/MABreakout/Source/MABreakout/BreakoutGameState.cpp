// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutGameState.h"
#include "Kismet/GameplayStatics.h"

ABreakoutGameState::ABreakoutGameState()
{
	lives = 3;
	bDefeat = false;
}

int ABreakoutGameState::GetLives()
{
	return lives;
}

void ABreakoutGameState::Defeat()
{
	bDefeat = true;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), DefeatSound, FVector(0, 0, 0));
}

void ABreakoutGameState::Victory()
{
	bVictory = true;
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), VictorySound,FVector(0,0,0));
}

bool ABreakoutGameState::IsDefeated()
{
	return bDefeat;
}

bool ABreakoutGameState::IsVictorious()
{
	return bVictory;
}
