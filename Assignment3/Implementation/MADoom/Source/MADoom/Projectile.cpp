// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
//Components
#include "Components/SphereComponent.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ExplosiveComponent.h"
//Utility
#include "EngineUtils.h"
//References
#include "PlayerCharacter.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create sphere root
	ProjectileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	ProjectileSphere->SetSphereRadius(20.f);
	ProjectileSphere->SetCollisionProfileName("OverlapAll");
	ProjectileSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProjectileSphere->SetSimulatePhysics(true);
	ProjectileSphere->SetEnableGravity(false);
	SetRootComponent(ProjectileSphere);
	//Create aoe
	ExplosiveComponent = CreateDefaultSubobject<UExplosiveComponent>(TEXT("Explosive Component"));
	ExplosiveComponent->ExplosionRadius->SetSphereRadius(AreaOfEffect);
	//Create sprite
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite Component"));
	SpriteComponent->SetLooping(true);
	SpriteComponent->SetupAttachment(RootComponent);
	//Create projectile movement component
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileComponent->UpdatedComponent = RootComponent;
	ProjectileComponent->ProjectileGravityScale = 0;
	ProjectileComponent->MaxSpeed = Speed;
	ProjectileComponent->InitialSpeed = Speed;
	//Subscribe to on hit
	ProjectileSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileComponent->MaxSpeed = Speed;
	ProjectileComponent->InitialSpeed = Speed;
	SpriteComponent->SetFlipbook(ProjectileSprite);
	
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner() && OtherActor != GetOwner()->GetOwner()) {
		if (OtherActor->ActorHasTag("CanDamage"))
		{
			//Simple projectile
			if (AreaOfEffect <= 0)
			{
				OtherActor->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), GetOwner());
			}
			//Explosive
			else
			{
				ExplosiveComponent->Explode(Damage, 1000.f);
			}
		}

		//Destroy self
		this->Destroy();
	}
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
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

