// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class UEMODES_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

	//PART 1
	UPROPERTY(EditAnywhere, Category = "Pawn Visual")
		class UPaperSpriteComponent* PawnSpriteComponent;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Camera")
		class UCameraComponent* FollowCamera;

	//PART 2

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class UBoxComponent* PlayerRootCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom")
		class USpringArmComponent* SpringArm;

	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Speed")
	float NormalSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement Speed")
	float FastSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void MoveForward(float value);

	void SpeedUp();
	void SlowDown();
private:
	float MovementForward;
	
	void SetDirection(const FVector Direction);
};
