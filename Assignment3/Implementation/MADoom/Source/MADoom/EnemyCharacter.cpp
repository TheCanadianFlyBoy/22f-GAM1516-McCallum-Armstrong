// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "PaperFlipbookComponent.h"
#include "PlayerCharacter.h"
#include "EngineUtils.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	//Add player tag
	Tags.Add("CanDamage");


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Enemy Sprite"));
	SpriteComponent->Stop();
	SpriteComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Orient sprite
	//Assumes single player
	for (TActorIterator<APlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr)
		{
			//Get direction to player
			AActor* Player = *ActorItr;
			FVector DeltaPosition = GetActorLocation() - Player->GetActorLocation();
			FRotator Direction = DeltaPosition.Rotation();
			//Face the sprite
			SpriteComponent->SetWorldRotation(Direction);
			SpriteComponent->AddLocalRotation(FRotator(0, 90.f, 0));
		}
	}

	//Movement animation
	if (GetLastMovementInputVector().Size() != 0.f)
	{
		SpriteComponent->Play();
	}
	else {
		SpriteComponent->Stop();
	}

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

