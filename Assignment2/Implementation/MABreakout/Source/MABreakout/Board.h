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

	// Sets default values for this actor's properties
	ABoard();
	//UFUNCTIONS
	UFUNCTION()
		void SpawnBall();
	UFUNCTION()
		UPrimitiveComponent* GetBottom();

public: //UPROPERTIES
	
	//BOARD PROPERTIES
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "SceneRoot")
		class USceneComponent* BoardRoot;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Board")
		class UCameraComponent* BoardCamera;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Board")
		class UPaperSpriteComponent* BoardBacking;

	int BallCount;


	//Pointers
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Board")
		int BrickCount;
	UPROPERTY(VisibleAnywhere, Category = "Board")
		class APaddlePawn* PlayerPaddle;
	UPROPERTY(VisibleAnywhere, Category = "Board")
		TArray<class ABall*> Balls;

	//Templates
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABrick> BrickTemplate;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<ABall> BallTemplate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateBoard();

private:

	class UBoxComponent* SideBottom;

	bool bLaunched;

	float boardWidth;
	float boardHeight;
	float borderWidth;

};
