// Fill out your copyright notice in the Description page of Project Settings.


#include "GooseEasterEgg.h"
#include "DoomGameState.h"
#include "BackgroundMusicComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AGooseEasterEgg::AGooseEasterEgg()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX COMPONENT"));
	BoxComponent->SetBoxExtent(FVector(250, 100, 100));
	BoxComponent->SetCollisionProfileName("OverlapAll");
	SetRootComponent(BoxComponent);

	//Subscribe
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AGooseEasterEgg::OnBeginOverlap);

}

// Called when the game starts or when spawned
void AGooseEasterEgg::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGooseEasterEgg::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ADoomGameState* State = (ADoomGameState*)GetWorld()->GetGameState();
	State->MusicComponent->TransitionMusic(Song);


}

// Called every frame
void AGooseEasterEgg::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

