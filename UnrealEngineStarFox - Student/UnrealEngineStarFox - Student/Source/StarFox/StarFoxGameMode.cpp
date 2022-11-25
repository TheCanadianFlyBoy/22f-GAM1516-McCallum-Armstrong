// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "StarFoxGameMode.h"
#include "StarFox.h"
#include "StarFoxPawn.h"

AStarFoxGameMode::AStarFoxGameMode()
{
	// set default pawn class to our flying pawn
    //TODO 40: SET the DefaultPawnClass of this GameMode to the AStarFoxPawn::???
	DefaultPawnClass = AStarFoxPawn::StaticClass();

    //TODO FINAL: Compile and go set up a environment that looks similar to mine and test out the Ship flying in 3D Space.
    //HAVE A LOOK AT THE INPUT SETTINGS, AND THE USE OF A GAMEPAD CONTROLLER AND MOTION CONTROLLER
}
