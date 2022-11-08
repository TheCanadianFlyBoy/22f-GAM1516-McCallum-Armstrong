// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddleController.h"
#include "Camera/CameraComponent.h"
#include "Board.h"
#include "EngineUtils.h" //Needed for TActorIterator

void APlayerPaddleController::BeginPlay()
{
    Super::BeginPlay();

    //Get and set camera
    for (TActorIterator<ABoard> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        //Nullptr check
        if (ActorItr->BoardCamera)
        {
            SetViewTarget(*ActorItr);
        }
    }

}
