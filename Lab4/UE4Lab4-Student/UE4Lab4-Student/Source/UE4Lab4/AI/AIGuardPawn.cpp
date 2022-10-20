// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGuardPawn.h"
#include "Components/CapsuleComponent.h"
#include "Utils/MyBlueprintFunctionLibrary.h"

//Lab Week 7 Implement: Sets default values for the AAIGuardPawn sub class
AAIGuardPawn::AAIGuardPawn()
{
    //COMMENT: Lock the CapsuleComponent's & Rotation
    //SET the CapsuleComponent's BodyInstance, bLockZRotation to false
    CapsuleComponent->BodyInstance.bLockZRotation = false;
    //CALL Empty() on Tags (This is a variable in AActor), Tags is a way to tag this actor with a game play tag. A tag is a label, so we can label this Actor with multiple tags  
    Tags.Empty();
    //CALL Add() on Tags, passing in : "AIGuard"
    Tags.Add("AIGuard");

}

//Lab Week 7 Implement: Move To Current Patrol Point
void AAIGuardPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    //COMMENT: Patrol Goal Checks
    //IF CurrentPatrolPoint IS NOT nullptr
    if (CurrentPatrolPoint != nullptr)
    {
    	//DECLARE a variable called Delta of type FVector, and Assign it to the result of:  GetActorLocation() - CurrentPatrolPoint->GetActorLocation()
        FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
    	//DECLARE a variable called DistanceToGoal of type float and assign it to the return value of :  Delta.Size()
        float DistanceToGoal = Delta.Size();

        //COMMENT Check if we are within 50 .. 100(Better with 2D) units of our goal, if so - pick a new patrol point
    	//IF DistanceToGoal IS LESS THAN 100
        if (DistanceToGoal < 100)
        {
        	//CALL MoveToNextPatrolPoint()
            MoveToNextPatrolPoint();
        }
    	//ENDIF


        //COMMENT: Slerp to the patrol point
    	//CALL SetActorLocation() passing in : FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 600.f)
        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 600.f));
    }
	//ENDIF
}

//Lab Week 7 Implement: Move to next Patrol Point if this Actor can patrol, and start the Spawn Projectile Timer
void AAIGuardPawn::BeginPlay()
{
    Super::BeginPlay();

    //IF bPatrol IS true
    if (bPatrol)
    {
    	//CALL MoveToNextPatrolPoint()
        MoveToNextPatrolPoint();
    }
    //ENDIF

    /*COMMENT: Spawn the projectile periodically*/
    //CREATE the SpawnProjectileTimer by Getting the World Timer Manager by calling  GetWorldTimerManager() and call SetTimer() passing in : SpawnProjectileTimer, this, &AAIGuardPawn::SpawnProjectile, FireTimerDelay, true
    GetWorldTimerManager().SetTimer(SpawnProjectileTimer, this, &AAIGuardPawn::SpawnProjectile, FireTimerDelay, true);
}

//Lab Week 7 Implement: pick a new patrol point by Setting the Current Patrol Point, and Rotate this Actor to the Current Patrol Points
void AAIGuardPawn::MoveToNextPatrolPoint()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "MoveToNextPatrolPoint - ");
    //COMMENT: Assign next patrol point.

    //IF CurrentPatrolPoint IS EQUAL nullptr || CurrentPatrolPoint IS EQUAL SecondPatrolPoint
    if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
    {
    	//SET CurrentPatrolPoint to FirstPatrolPoint
        CurrentPatrolPoint = FirstPatrolPoint;

    }
    //ELSE
    else
    {
    	//SET CurrentPatrolPoint to SecondPatrolPoint
        CurrentPatrolPoint = SecondPatrolPoint;
    }
    //ENDIF

    //DECLARE a variable called Direction of type FVector and assign it to : GetActorLocation() - CurrentPatrolPoint->GetActorLocation()
    FVector Direction = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
    //CALL Normalize() on Direction
    Direction.Normalize();

    //DECLARE a variable called NewLookAt of type FRotator and assign it to the return value of:  FRotationMatrix::MakeFromX(Direction).Rotator()
    FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
    //SET NewLookAt.Pitch to 0
    NewLookAt.Pitch = 0;
    //SET NewLookAt.Roll to 0
    NewLookAt.Roll = 0;
    //INCREMENT NewLookAt.Yaw by -180 i.e NewLookAt.Yaw += -180.0f;
    NewLookAt.Yaw += -180.0f;
    //CALL SetActorRotation() passing in NewLookAt
    SetActorRotation(NewLookAt);
}
