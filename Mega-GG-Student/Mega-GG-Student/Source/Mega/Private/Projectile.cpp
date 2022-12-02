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

    /** paper flipbook component  */
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

   /* AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
    AudioComponent->bAutoActivate = false;
    AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    AudioComponent->SetupAttachment(RootComponent);*/

    //Particle Systems//

    static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Explosion'"));
    if (PS.Succeeded())
    {
        ProjectileFX = PS.Object;
    }
    //PSC = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
    ////PSC->SetTemplate(PS.Object); //If you want it to Spawn on Creation, could go to BeginPlay too
    //PSC->SetupAttachment(RootComponent);

    /** projectiles not intended to live forever  */
    InitialLifeSpan = 5.f;
}

void AProjectile::SetFireDirection(FVector dir)
{
    ProjectileMovementComponent->Velocity = InitialSpeed * dir;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

  //  ProjectileMovementComponent->Velocity = FVector(InitialSpeed, 0, 0);
}


//ICA 3 Implement: Destroy the Other Actor that has been Shot, 
//Hint: The OtherActor is either the AIGuard or Player
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    // Other Actor is the actor that triggered the event. Check that is not ourself. 
    if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && !IsPendingKill())
    {
        if (OtherActor != this->GetOwner())
        {
          //  if (OtherActor->ActorHasTag("AIGuard") || OtherActor->ActorHasTag("Player"))
          //  {
           /* if (!AudioComponent->IsPlaying()) {
                AudioComponent->SetSound(ImpactSound);
                AudioComponent->Play();
            }*/
            UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
                if (ProjectileFX)
                {
                   

                    //Spawn ParticleSystem using GamePlayStatics
                    UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
                    //OR Spawn Particle using UParticleSystemComponent
                   // PSC->SetTemplate(ProjectileFX);
                    //ProjectileSprite->bHiddenInGame = true;
                    //ProjectileSprite->SetVisibility(false);
                }
                 Destroy();
        //    }

        }
    }
}
