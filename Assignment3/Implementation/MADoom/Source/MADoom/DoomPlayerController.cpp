// Fill out your copyright notice in the Description page of Project Settings.


#include "DoomPlayerController.h"
#include "PlayerCharacter.h"
#include "InventoryComponent.h"
#include "Camera/CameraComponent.h"
#include "DoomPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"

void ADoomPlayerController::OnPossess(APawn* aPawn)
{
    //Call super
    Super::OnPossess(aPawn);
    if (!MyPawn) {
        //Cast
        MyPawn = (APlayerCharacter*)aPawn;
        //Set target
        SetViewTarget(MyPawn);

        //Set pointer to self
        MyPawn->MyController = this;

        //Bind axes of movement and view
        InputComponent->BindAxis("LookUp", this, &ADoomPlayerController::LookUp);
        InputComponent->BindAxis("LookRight", this, &ADoomPlayerController::LookRight);
        InputComponent->BindAxis("MoveRight", MyPawn, &APlayerCharacter::MoveRight);
        InputComponent->BindAxis("MoveForward", MyPawn, &APlayerCharacter::MoveForward);
        //Bind movement/manipualtion actions
        InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, MyPawn, &APlayerCharacter::Jump);
        InputComponent->BindAction("Interact", EInputEvent::IE_Pressed, MyPawn, &APlayerCharacter::Interact);
        //Bind inventory actions
        InputComponent->BindAction("NextWeapon", EInputEvent::IE_Released, MyPawn, &APlayerCharacter::NextWeapon);
        InputComponent->BindAction("PreviousWeapon", EInputEvent::IE_Released, MyPawn, &APlayerCharacter::PreviousWeapon);
        //Bind weapon actions
        InputComponent->BindAction("PrimaryFire", EInputEvent::IE_Pressed, MyPawn, &APlayerCharacter::BeginFire); //TODO - remove gun "jamming"
        InputComponent->BindAction("PrimaryFire", EInputEvent::IE_Released, MyPawn, &APlayerCharacter::EndFire);
        //Bind exit
        InputComponent->BindAction("Exit", EInputEvent::IE_Released, this, &ADoomPlayerController::Exit);
    }
}

void ADoomPlayerController::OnUnPossess()
{
    Super::OnUnPossess();
;
}

void ADoomPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

void ADoomPlayerController::BeginPlay()
{
    Super::BeginPlay();
}


void ADoomPlayerController::Exit()
{
    UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}

void ADoomPlayerController::LookUp(float Value)
{
    ADoomPlayerState* MyState = (ADoomPlayerState*)GetPawn()->GetPlayerState();
    if (!MyState->IsDead()) {
        AddPitchInput(-Value);
    }
}

void ADoomPlayerController::LookRight(float Value)
{
    ADoomPlayerState* MyState = (ADoomPlayerState*)GetPawn()->GetPlayerState();
    if (!MyState->IsDead()) {
        AddYawInput(Value);
    }
}
