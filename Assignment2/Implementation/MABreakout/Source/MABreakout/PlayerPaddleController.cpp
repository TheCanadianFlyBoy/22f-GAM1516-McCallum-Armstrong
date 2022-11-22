// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPaddleController.h"
#include "Camera/CameraComponent.h"
#include "Board.h"
#include "PaddlePawn.h"
#include "EngineUtils.h" //Needed for TActorIterator
#include "Kismet/KismetSystemLibrary.h"

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

    InputComponent->BindAction("Exit", EInputEvent::IE_Released, this, &APlayerPaddleController::Exit);

}

void APlayerPaddleController::OnPossess(APawn* aPawn)
{
    MyPawn = Cast<APaddlePawn>(aPawn);

    InputComponent->BindAxis("MoveRight", MyPawn, &APaddlePawn::MoveRight);  

}

void APlayerPaddleController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());

    Super::OnUnPossess();
}

void APlayerPaddleController::SetupInputComponent()
{
    Super::SetupInputComponent();

}

void APlayerPaddleController::Exit()
{
    UKismetSystemLibrary::QuitGame(this,this, EQuitPreference::Quit,false);
}

void APlayerPaddleController::MoveRight(float _value)
{
    if (MyPawn)
    {
        MyPawn->MoveRight(_value);
    }
}
