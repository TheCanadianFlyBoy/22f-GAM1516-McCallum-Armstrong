// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/PlayerPawn.h"
#include "AIGuardPawn.generated.h"

/**
 * 
 */
UCLASS()
class UE4LAB4_API AAIGuardPawn : public APlayerPawn
{
	GENERATED_BODY()
	
public:
    AAIGuardPawn();
	
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /* Let the guard go on patrol */
    UPROPERTY(EditInstanceOnly, Category = "AI")
        bool bPatrol;

    /* First of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* FirstPatrolPoint;

    /* Second of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* SecondPatrolPoint;

    // The current point the actor is either moving to or standing at
    AActor* CurrentPatrolPoint;

    UFUNCTION() //WIthout this, the function will be inlined and optimized out
        void MoveToNextPatrolPoint();
    

private:
    FTimerHandle SpawnProjectileTimer;

};
