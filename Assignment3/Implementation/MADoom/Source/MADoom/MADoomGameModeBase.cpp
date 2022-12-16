// Copyright Epic Games, Inc. All Rights Reserved.


#include "MADoomGameModeBase.h"
#include "EngineUtils.h" //Needed for TActorIterator
#include "Kismet/GameplayStatics.h"

void AMADoomGameModeBase::BeginPlay()
{
    //DECLARE a FString variable called command and assign it to "show collision"
    FString command = "show collision";

    //DECLARE a variable called controller of type APlayerController* and assign it to the return value of: UGameplayStatics::GetPlayerController(GetWorld(), 0)
    APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

    if (controller) //Uncomment
    {
        //CALL ConsoleCommand() on controller passing in command, false
       // controller->ConsoleCommand(command, false);
        //SET bShowMouseCursor on controller to true
        //controller->bShowMouseCursor = true; //TODO - cleanup
        //SET bEnableClickEvents on controller to true
        controller->bEnableClickEvents = true;
        //SET bEnableMouseOverEvents on controller to true
        controller->bEnableMouseOverEvents = true;
    }
}