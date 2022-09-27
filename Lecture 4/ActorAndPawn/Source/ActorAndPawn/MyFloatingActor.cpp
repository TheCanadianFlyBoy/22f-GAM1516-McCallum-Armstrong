// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFloatingActor.h"

//Constructor
AMyFloatingActor::AMyFloatingActor()
{
    PrimaryActorTick.bCanEverTick = true;
}

//Game start/spawn
void AMyFloatingActor::BeginPlay()
{
    Super::BeginPlay();
}

//Update 
void AMyFloatingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //Create vector, set to current location
    FVector NewLocation = GetActorLocation();
    //Calculate DeltaHeight per frame. Delta height is on sine wave
    float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
    NewLocation.X += DeltaHeight * XValue;
    NewLocation.Y += DeltaHeight * YValue;
    NewLocation.Z += DeltaHeight * ZValue;

    //Increment running time
    RunningTime += DeltaTime;

    //Set Actor to new loc
    SetActorLocation(NewLocation);
}
