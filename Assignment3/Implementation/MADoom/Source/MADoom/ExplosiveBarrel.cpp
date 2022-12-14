// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "PlayerCharacter.h"

#include "PaperFlipbookComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "ExplosiveComponent.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
	//Add tag
	Tags.Add("CanDamage");

	//Set defaults
	Damage = 50.f;
	DamageRadius = 200.f;

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision Capsule"));
	CapsuleComponent->SetCapsuleRadius(50.f);
	CapsuleComponent->SetCapsuleHalfHeight(40.f);
	CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	CapsuleComponent->BodyInstance.bLockRotation = true;
	CapsuleComponent->BodyInstance.bLockXRotation = true;
	CapsuleComponent->BodyInstance.bLockYRotation = true;
	CapsuleComponent->BodyInstance.bLockZRotation = true;
	SetRootComponent(CapsuleComponent);
	//Create explosive
	ExplosiveComponent = CreateDefaultSubobject<UExplosiveComponent>(TEXT("Explosive Component"));
	ExplosiveComponent->ExplosionRadius->SetSphereRadius(DamageRadius);
	ExplosiveComponent->SetupAttachment(RootComponent);
	//Create sprite
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpriteComponent->Stop();
	SpriteComponent->SetLooping(false);
	SpriteComponent->SetupAttachment(RootComponent);
	//Create sound component
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Component"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetupAttachment(RootComponent);

	//Subscribe to damage
	this->OnTakeAnyDamage.AddDynamic(this, &AExplosiveBarrel::OnShot);

}

void AExplosiveBarrel::Explode()
{
	//Check if explosion already in progress
	if (!GetWorldTimerManager().IsTimerActive(ExplosionTimerHandle))
	{
		//Play components
		AudioComponent->Play();
		SpriteComponent->Play();
		//Set end in progress
		GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &AExplosiveBarrel::EndExplode, SpriteComponent->GetFlipbookLength(), true);

		ExplosiveComponent->Explode(Damage, 1000.f);

	}
}

void AExplosiveBarrel::EndExplode()
{
	//Delete sprite component
	if (SpriteComponent->IsVisible())
	{
		GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &AExplosiveBarrel::EndExplode, 3.f, true);
		SpriteComponent->SetVisibility(false);
	}
	else {
		//Destroy self
		this->Destroy();
	}
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosiveBarrel::OnShot(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageInstigator)
{
	Explode();
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

}

// Called to bind functionality to input
void AExplosiveBarrel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
