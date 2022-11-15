// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddleController.h"
#include "Camera/CameraComponent.h"
#include "Board.h"
#include "PaddlePawn.h"
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
            MyBoard = *ActorItr;
            InputComponent->BindAction("Launch", EInputEvent::IE_Released, MyBoard, &ABoard::SpawnBall);
            SetViewTarget(*ActorItr);
        }
    }

}

void APlayerPaddleController::OnPossess(APawn* aPawn)
{
    MyPawn = Cast<APaddlePawn>(aPawn);
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::Possess: - " + aPawn->GetName());
    InputComponent->BindAxis("MoveRight", MyPawn, &APaddlePawn::MoveRight);  

}

void APlayerPaddleController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());
    if (posessedPawn)
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::UnPossess: - " + GetOwner()->GetName());

    Super::OnUnPossess();
}

void APlayerPaddleController::SetupInputComponent()
{
    Super::SetupInputComponent();

}

void APlayerPaddleController::AcknowledgePossession(APawn* PossesedPawn)
{
}

void APlayerPaddleController::MoveRight(float _value)
{
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, "Moving");
    if (MyPawn)
    {
        MyPawn->MoveRight(_value);
    }
}
