// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstActor.h"
#include "PaperSpriteComponent.h"

// Sets default values
AMyFirstActor::AMyFirstActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set sprite
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Actor Visual");
	//Attach sprite to actor RootComponent
	Sprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMyFirstActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyFirstActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

