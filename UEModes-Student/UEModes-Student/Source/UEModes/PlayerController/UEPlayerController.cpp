// Fill out your copyright notice in the Description page of Project Settings.


#include "UEPlayerController.h"
#include "UEModes/Pawn/CollidingPawn.h"
#include "UEModes/PlayerState/UEPlayerState.h"

void AUEPlayerController::OnPossess(APawn* aPawn)
{
    Super::OnPossess(aPawn);

    MyPawn = Cast<ACollidingPawn>(aPawn);
    GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, "AMyPlayerController::Possess: - " + aPawn->GetName());

    InputComponent->BindAxis("MoveForward", MyPawn, &ACollidingPawn::MoveForward);
    InputComponent->BindAction("Speed", IE_Pressed, MyPawn, &ACollidingPawn::SpeedUp);
    InputComponent->BindAction("Speed", IE_Released, MyPawn, &ACollidingPawn::SlowDown);
}

void AUEPlayerController::OnUnPossess()
{
    APawn* posessedPawn = Cast<APawn>(GetOwner());
    if (posessedPawn)
        GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow,"AMyPlayerController::UnPossess: - " + GetOwner()->GetName());

    Super::OnUnPossess();
}

void AUEPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    MyPlayerState = Cast<AUEPlayerState>(PlayerState);
    if (MyPlayerState)
    {
        UE_LOG(LogTemp, Warning, TEXT("Found class %s"), TEXT("AMyPlayerController::BeginPlay: MyPlayerState Set"));
    }
    if (InputComponent != nullptr)
    {
    }
}

void AUEPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{

}

void AUEPlayerController::MoveForward(float value)
{
   
    if (MyPawn)
        MyPawn->MoveForward(value);
}

void AUEPlayerController::SpeedUp()
{
	if(MyPawn)
		MyPawn->SpeedUp();
}

void AUEPlayerController::SlowDown()
{
    if (MyPawn)
        MyPawn->SlowDown();
}
