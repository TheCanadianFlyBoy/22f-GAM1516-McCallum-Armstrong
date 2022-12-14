// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ExplosiveBarrel.generated.h"

UCLASS()
class MADOOM_API AExplosiveBarrel : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AExplosiveBarrel();

	//Components
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere, Category = "DOOM Component")
		class UPaperFlipbookComponent* SpriteComponent;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Component")
		class UExplosiveComponent* ExplosiveComponent;
	//Stats
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "DOOM Stats")
		float DamageRadius;
	//Sound
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DOOM Sound")
		class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Sound")
		class USoundBase* FireSound;



	void Explode();
	void EndExplode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnShot(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageInstigator);

	FTimerHandle ExplosionTimerHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:


};
