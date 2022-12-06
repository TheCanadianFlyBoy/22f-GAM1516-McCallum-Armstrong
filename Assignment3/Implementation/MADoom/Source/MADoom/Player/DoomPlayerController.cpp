// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomPlayerController.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

void ADoomPlayerController::OnPossess(APawn* aPawn)
{
    //Call super
    Super::OnPossess(aPawn);
    //Cast
    MyPawn = Cast<APlayerCharacter>(aPawn);
    //Set target
    SetViewTarget(MyPawn);
    //Bind axes
    InputComponent->BindAxis("LookUp",      this, &ADoomPlayerController::LookUp);
    InputComponent->BindAxis("LookRight",   this, &ADoomPlayerController::LookRight);
    InputComponent->BindAxis("MoveRight", MyPawn, &APlayerCharacter::MoveRight);
    InputComponent->BindAxis("MoveForward", MyPawn, &APlayerCharacter::MoveForward);
    //Bind actions
    InputComponent->BindAction("Jump",EInputEvent::IE_Released, MyPawn, &APlayerCharacter::Jump); 



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
    AddPitchInput(-Value);
}

void ADoomPlayerController::LookRight(float Value)
{
    AddYawInput(Value);
}
