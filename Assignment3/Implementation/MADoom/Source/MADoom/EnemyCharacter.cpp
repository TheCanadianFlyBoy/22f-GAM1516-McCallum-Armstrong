// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
//Components
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//Utilities
#include "PlayerCharacter.h"
#include "EngineUtils.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	//Add player tag
	Tags.Add("CanDamage");

	Health = MaxHealth;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Enemy Sprite"));
	SpriteComponent->Stop();
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Set speed
	GetCharacterMovement()->MaxWalkSpeed = 500.f * MaxSpeed;
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
			FRotator SpriteDirection = DeltaPosition.Rotation();
			//Face the sprite
			SpriteComponent->SetWorldRotation(SpriteDirection);
			SpriteComponent->AddLocalRotation(FRotator(0, 90.f, 0));
			//Set directional sprite
			FRotator CharacterDirection = SpriteDirection - GetActorForwardVector().Rotation();
			float DeltaDirection = CharacterDirection.Yaw - SpriteDirection.Yaw;
			if (DeltaDirection > 45.f)
			{
				SpriteComponent->SetFlipbook(WalkSprite_Left);
			}
			else if (DeltaDirection < -45.f)
			{
				SpriteComponent->SetFlipbook(WalkSprite_Right);
			}
			else {
				SpriteComponent->SetFlipbook(WalkSprite_Forward);
			}
		}
	}
	

	//Movement animation
	if (GetCharacterMovement()->Velocity.Size() != 0.f)
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

void AEnemyCharacter::MoveForward(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AEnemyCharacter::MoveRight(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}

