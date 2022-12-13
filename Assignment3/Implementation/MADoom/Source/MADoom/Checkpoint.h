// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class MADOOM_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

	UPROPERTY(VisibleAnywhere, Category = "DOOM Save")
		class USaveStateComponent* SaveComponent;
	UPROPERTY(VisibleAnywhere, Category = "DOOM Save")
		class USphereComponent* TriggerZone;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//Save state function
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void LoadSaveState(class APlayerCharacter* Player);

};
