// Fill out your copyright notice in the Description page of Project Settings.


#include "UEGameMode.h"
#include "EngineUtils.h" //Needed for TActorIterator
#include "Kismet/GameplayStatics.h"
void AUEGameMode::BeginPlay()
{
    Super::BeginPlay();
    //FOR TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr
    
    {
    	//CALL AddOnScreenDebugMessage() on GEngine passing in: -1, 15.0f, FColor::Green, "Actor: " + ActorItr->GetName()
    
    }
    //ENDFOR

   //DECLARE a FString variable called command and assign it to "show collision"
   
   //DECLARE a variable called controller of type APlayerController* and assign it to the return value of: UGameplayStatics::GetPlayerController(GetWorld(), 0)
   

    //if (controller) //Uncomment
    {
    	//CALL ConsoleCommand() on controller passing in command, false
   
	//SET bShowMouseCursor on controller to true
   
        //SET bEnableClickEvents on controller to true
   
        //SET bEnableMouseOverEvents on controller to true
   

    }
}
