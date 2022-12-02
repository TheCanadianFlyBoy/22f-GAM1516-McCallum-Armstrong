// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomPlayerController.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

void ADoomPlayerController::OnPossess(APawn* aPawn)
{
    MyPawn = Cast<APlayerCharacter>(aPawn);

    InputComponent->BindAxis("MoveRight",   MyPawn, &APlayerCharacter::MoveRight);
    InputComponent->BindAxis("MoveForward", MyPawn, &APlayerCharacter::MoveForward);
    InputComponent->BindAxis("LookUp",      this, &ADoomPlayerController::LookUp);
    InputComponent->BindAxis("LookRight",   this, &ADoomPlayerController::LookRight);
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

void ADoomPlayerController::LookUp(float Value)
{
    AddPitchInput(Value);
    MyPawn->CameraComponent->AddLocalRotation(FRotator(Value, 0.f, 0.f));
}

void ADoomPlayerController::LookRight(float Value)
{
    AddYawInput(Value);
}
