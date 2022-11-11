// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"

#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ConstructorHelpers.h"
#include "PaperSprite.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

AProjectile::AProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    /** sphere collision  */
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetSphereRadius(4.f);
    SphereComponent->BodyInstance.SetCollisionProfileName("BlockAll");
    SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(SphereComponent);
    SphereComponent->BodyInstance.bLockXRotation = true;
    SphereComponent->BodyInstance.bLockYRotation = true;
    SphereComponent->BodyInstance.bLockZRotation = true;
    SphereComponent->BodyInstance.bLockYTranslation = true;
    RootComponent = SphereComponent;

    /** paper sprite component  */
    ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperFlipbookComponent"));
    ProjectileSprite->SetupAttachment(RootComponent);
    ProjectileSprite->SetRelativeLocation(FVector(-3.f, 0.f, 0.f));

    /** ProjectileMovementComponent  */
    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    ProjectileMovementComponent->UpdatedComponent = SphereComponent;
    ProjectileMovementComponent->InitialSpeed = InitialSpeed;
    ProjectileMovementComponent->MaxSpeed = MaximumSpeed;

    ProjectileMovementComponent->bRotationFollowsVelocity = false;
    ProjectileMovementComponent->bShouldBounce = true;
      
    //Particle Systems//
    //Week 9 Lab: The code below loads a particle system asset from the content directory. Read the documentation for ConstructorHelpers::FObjectFinder
    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion'"));
	//IF loading the particle system succeeded 
    if (PS.Succeeded())
    {
    	//We then Assign the loaded Particle System Object to the ProjectileFX pointer
        ProjectileFX = PS.Object;
    }
    //ENDIF
	
    /** projectiles not intended to live forever  */
    InitialLifeSpan = 5.f;
}

//Week 9 Lab : Set the Projectiles Velocity based on the BP value and passed in direction
void AProjectile::SetFireDirection(FVector dir)
{
	//SET ProjectileMovementComponent->Velocity to InitialSpeed * dir
    ProjectileMovementComponent->Velocity = InitialSpeed * dir;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();
}

//Week 9 Lab : Destroy this Actor Spawn the ProjectileFX and play the ImpactSound. Make sure it is not destroyed if it collides with the Player or Weapon
//Hint: Use UGameplayStatics::PlaySoundAtLocation() and UGameplayStatics::SpawnEmitterAtLocation()
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Other Actor is the actor that triggered the event. Check that is not ourself.	
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && !IsPendingKill())
    {
        if (OtherActor != this->GetOwner())
        {
        	//CALL UGameplayStatics::PlaySoundAtLocation() passing in GetWorld(), ImpactSound, GetActorLocation()
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, GetActorLocation());
        	//IF ProjectileFX is not null
            if (ProjectileFX)
            {
            	//CALL UGameplayStatics::SpawnEmitterAtLocation() passing in this, ProjectileFX, GetActorLocation()
                UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
            }        	        	
        	//ENDIF

        	//Destroy this Projectile
            this->Destroy();
        }
    }
}
