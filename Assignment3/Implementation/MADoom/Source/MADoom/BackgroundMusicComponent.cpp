// Fill out your copyright notice in the Description page of Project Settings.


#include "BackgroundMusicComponent.h"
//Components
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UBackgroundMusicComponent::UBackgroundMusicComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->Sound = DefaultBackgroundMusic;

	// ...
}


void UBackgroundMusicComponent::TransitionMusic(USoundBase* Song)
{
	//Null check
	if (Song)
	{
		//Case 1: instant play
		if (!AudioComponent->IsPlaying())
		{
			//Play
			AudioComponent->Sound = Song;
			AudioComponent->Play();
		}
		else {
			//Fade and recall
			AudioComponent->FadeOut(3.f, 0.f, EAudioFaderCurve::Logarithmic);
			QueuedMusic = Song;
			GetWorld()->GetTimerManager().SetTimer(FadeTimerHandle, this, &UBackgroundMusicComponent::PlayQueuedSong, 3.f);
		}

	}
}

// Called when the game starts
void UBackgroundMusicComponent::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->Sound = DefaultBackgroundMusic;
	// ...
	
}

void UBackgroundMusicComponent::Play()
{
	AudioComponent->Play();
}

void UBackgroundMusicComponent::PlayQueuedSong()
{
	if (QueuedMusic)
	{
		//Dequeue
		AudioComponent->Sound = QueuedMusic;
		QueuedMusic = nullptr;
		//Play
		AudioComponent->Play();
	}
}


// Called every frame
void UBackgroundMusicComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

