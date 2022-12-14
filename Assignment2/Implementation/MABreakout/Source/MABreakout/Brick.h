// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

UCLASS()
class MABREAKOUT_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

	// Collision Box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision Box")
		class UBoxComponent* BoxComponent;
	//Flipbook
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Brick", meta = (AllowPrivateAccess = "true"))
		class UPaperFlipbookComponent* BrickFlipbook;
	//Health Points
	UPROPERTY(VisibleAnywhere, Category = "Brick")
		float HealthPoints;
	// Chance of Powerup Drop
	UPROPERTY(VisibleAnywhere, Category = "Brick")
		float PowerupChance;
	//Powerup template
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class APowerup> PowerupTemplate;
	//Sound
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects", meta = (AllowPrivateAccess = "true"))
		class USoundBase* BreakSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//On hit
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Roll for powerup on destruction
	void RollForPowerup();

	//Update sprite
	void UpdateSprite();

};
