// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BackgroundMusicComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MADOOM_API UBackgroundMusicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBackgroundMusicComponent();

	UPROPERTY(VisibleAnywhere, Category = "DOOM Music")
		class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Music")
		class USoundBase* DefaultBackgroundMusic;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DOOM Music")
		class USoundBase* DefaultVictoryMusic;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DOOM Music")
		class USoundBase* QueuedMusic;

	virtual void Play();
	void TransitionMusic(USoundBase* Song);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	FTimerHandle FadeTimerHandle;
	void PlayQueuedSong();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
