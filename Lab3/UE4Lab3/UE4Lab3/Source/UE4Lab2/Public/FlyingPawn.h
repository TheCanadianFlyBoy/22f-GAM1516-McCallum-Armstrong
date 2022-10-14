// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class UPaperSpriteComponent;
class USpringArmComponent;
class UCameraComponent;
class UFloatingPawnMovement;

#include "CoreMinimal.h"
#include "FlyingPawn.generated.h"

UCLASS()
class UE4LAB2_API AFlyingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFlyingPawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		USceneComponent* PlayerRoot;

	UPROPERTY(EditAnywhere, Category = "Pawn Visual")
		UPaperSpriteComponent* PawnSpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Pawn Camera")
		UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floating Movement")
		UFloatingPawnMovement* FloatingPawnMovement;

private:
	bool bGrowing;
	float MovingForward;

protected: //Methods
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Growth
	void StartGrowing();
	void StopGrowing();

	void FlyUp(float value);
	void FlyRight(float value);

	void MovingLeft();
	void MovingRight();

	void SetDirection(const FVector Direction);

public:	//Methods
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
