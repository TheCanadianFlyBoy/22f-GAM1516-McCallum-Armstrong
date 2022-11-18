// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Board.generated.h"

UCLASS()
class MABREAKOUT_API ABoard : public AActor
{
	GENERATED_BODY()
	
public:	
	//Enum for sides
	enum class BoardSide {
		Left,
		Right,
		Top,
		Bottom
	};


	// Sets default values for this actor's properties
	ABoard();

public: //UPROPERTIES
	
	//BOARD PROPERTIES
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "SceneRoot")
		class USceneComponent* BoardRoot;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Board")
		TArray<class UBoxComponent*> BoxColliders;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Board")
		class UCameraComponent* BoardCamera;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Board")
		class UPaperSpriteComponent* BoardBacking;

	int BallCount;


	//Pointers
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Board")
		TArray<class ABrick*> Bricks;
	UPROPERTY(VisibleAnywhere, Category = "Board")
		class APaddlePawn* PlayerPaddle;
	UPROPERTY(VisibleAnywhere, Category = "Board")
		TArray<class ABall*> Balls;

	//Templates
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABrick> BrickTemplate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABall> BallTemplate;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UFUNCTION()
		void SpawnPowerup(ABrick* _brick);
	UFUNCTION()
		void SpawnBall();
	UFUNCTION()
		UPrimitiveComponent* GetBottom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Box component hit
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateBoard();

private:

	UBoxComponent* SideBottom;

	bool bLaunched;

	float boardWidth;
	float boardHeight;
	float borderWidth;

};
