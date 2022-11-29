// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomPlayerController.h"
#include "PlayerCharacter.h"

void ADoomPlayerController::OnPossess(APawn* aPawn)
{
    MyPawn = Cast<APlayerCharacter>(aPawn);

    InputComponent->BindAxis("MoveRight",   MyPawn, &APlayerCharacter::MoveRight);
    InputComponent->BindAxis("MoveForward", MyPawn, &APlayerCharacter::MoveForward);
    InputComponent->BindAxis("LookUp",      MyPawn, &APlayerCharacter::LookUp);
    InputComponent->BindAxis("LookRight",   MyPawn, &APlayerCharacter::LookRight);
    //TODO InputComponent->BindAction("Exit", EInputEvent::IE_Released, this, &APlayerPaddleController::Exit);

    SetViewTarget(MyPawn);

}

void ADoomPlayerController::OnUnPossess()
{
    Super::OnUnPossess();
}

void ADoomPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void ADoomPlayerController::Exit()
{
}
