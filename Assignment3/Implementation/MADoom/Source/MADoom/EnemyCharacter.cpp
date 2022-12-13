// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
//Components
#include "PaperFlipbookComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
//References
#include "PlayerCharacter.h"
//Utilities
#include "Projectile.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	//Add player tag
	Tags.Add("CanDamage");

	MaxHealth = 50.f;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Sprite
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Enemy Sprite"));
	SpriteComponent->Stop();
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->AddLocalOffset(FVector(0, 0, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));

	//Audio
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(RootComponent);

	//Sensory
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing Component"));

	//Subscribe damage
	this->OnTakeAnyDamage.AddDynamic(this, &AEnemyCharacter::OnShot);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Set health
	Health = MaxHealth;
	//Set speed
	GetCharacterMovement()->MaxWalkSpeed = 500.f * MaxSpeed;
}

//On being shot
void AEnemyCharacter::OnShot(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageInstigator)
{
	if (Health > 0)
	{
		Health -= DamageAmount;
	}
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
			//If dead
			if (Health <= 0)
			{
				//Set appropriate flipbook
				SpriteComponent->SetFlipbook(DeathSprite_Standard);
				SpriteComponent->SetLooping(false);
				//if controller exists, delete it
				if (Controller)
				{
					Controller->Destroy();
				}
				//Set collision to inactive
				this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
			}
			//Else, do directional stuff
			else if (DeltaDirection > 45.f)
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
	if (GetCharacterMovement()->Velocity.Size() != 0.f || Health <= 0)
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

void AEnemyCharacter::Fire()
{
	//Play animation
	SpriteComponent->Play();
	AudioComponent->SetSound(FireSound);
	AudioComponent->Play();

	//Projectile Spawn
	if (ProjectileTemplate)
	{
		//TODO
	}
	else //Line Trace
	{
		//Generate hit
		AActor* hit = GetPickableActor_LineTraceSingleByChannel(ECollisionChannel::ECC_Pawn);
		//On hit
		if (hit && hit->ActorHasTag("CanDamage"))
		{
			//Take damage
			hit->TakeDamage(WeaponDamage, FDamageEvent(), this->GetController(), this);
		}
	}

}

AActor* AEnemyCharacter::GetPickableActor_LineTraceSingleByChannel(ECollisionChannel Channel)
{
	//Do line trace
	{

		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;
		SetupRay(StartTrace, Direction, EndTrace);

		//Setup parameters
		FCollisionQueryParams TraceParams;
		SetupTraceParams(TraceParams);

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		World->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, Channel, TraceParams); // simple trace function  ECC_PhysicsBody
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 1, 0, 5.f);
		return Hit.GetActor();
	}

	return nullptr;
}

void AEnemyCharacter::SetupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace)
{
	StartTrace = GetActorLocation(); // trace start is the camera location
	Direction = GetActorForwardVector() + (FVector(FMath::RandRange(-1,1), FMath::RandRange(-1, 1), FMath::RandRange(-1, 1)) * Accuracy);
	EndTrace = StartTrace + Direction * 5000.f; // and trace end is the camera location + an offset in the direction you are looking, the 5000 is the distance at which it checks
}

void AEnemyCharacter::SetupTraceParams(FCollisionQueryParams& TraceParams)
{
	TraceParams.AddIgnoredActor(this);	//Ignore weapon
	TraceParams.AddIgnoredActor(this->GetOwner()); //Ignore weapon owner
	TraceParams.bTraceComplex = true;	//Complex collision
	TraceParams.bReturnPhysicalMaterial = true;
}

