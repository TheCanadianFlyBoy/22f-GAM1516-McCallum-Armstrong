// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MoveToPawn.generated.h"

UCLASS()
class UEMODES_API AMoveToPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMoveToPawn();

	UPROPERTY(EditAnywhere, Category = "Pawn Visual")
		class UPaperSpriteComponent* PawnSpriteComponent;

	UPROPERTY(EditInstanceOnly,
		Category = "AI",
		meta = (EditCondition = "Target"))
		AActor* Target;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
