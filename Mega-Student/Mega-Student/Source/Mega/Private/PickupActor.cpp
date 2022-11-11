// Fill out your copyright notice in the Description page of Project Settings.

#include "PickupActor.h"
#include <Components/SphereComponent.h>
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "PaperSpriteComponent.h"

#include "MyBlueprintFunctionLibrary.h"
// Sets default values
APickupActor::APickupActor()
{
    Sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
    Sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Sprite->SetCollisionProfileName("NoCollision");

    SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereCollision->SetSphereRadius(24.f);
    RootComponent = SphereCollision;
    SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereCollision->SetCollisionProfileName("OverlapAll");
    SphereCollision->SetGenerateOverlapEvents(true);

    SphereCollision->SetSimulatePhysics(false);

    Sprite->SetupAttachment(RootComponent);
    
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(SphereCollision);
    Tags.Add("Pickup");
}

// Called when the game starts or when spawned
void APickupActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APickupActor::Disable()
{
	if (Sprite)
	{
		this->SetActorHiddenInGame(true);
        SphereCollision->SetActive(false);
        SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APickupActor::Enable()
{
	if (Sprite)
	{
		this->SetActorHiddenInGame(false);
        SphereCollision->SetActive(true);
        SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}
