// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutGameState.h"

ABreakoutGameState::ABreakoutGameState()
{
	lives = 3;
	totalScore = 0;
	bDefeat = false;
}

int ABreakoutGameState::GetScore()
{
	return totalScore;
}

int ABreakoutGameState::GetLives()
{
	return lives;
}

void ABreakoutGameState::DefeatPlayer()
{
	bDefeat = true;
}
