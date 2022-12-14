// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaddlePawn.generated.h"

UCLASS()
class MABREAKOUT_API APaddlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APaddlePawn();

	//Paddle length
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle")
		float PaddleLength;
	//Paddle maximum length
	UPROPERTY(EditAnywhere, Category = "Paddle")
		float PaddleMax;

	//Paddle Box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle")
		class UBoxComponent* BoxComponent;
	//Sprite
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Paddle")
		class UPaperSpriteComponent* PawnSpriteComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Paddle")
		float Speed;

	float MovementRight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Movement functionality
	void MoveRight(float Value);

	//Powerup functions
	void PaddlePlus();
	void PaddleMinus();

	void Regenerate();

private:
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
