// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "PaperSpriteComponent.h"
#include "ConstructorHelpers.h"
#include "PaperFlipbook.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Pawns/PlayerPawn.h"
#include "AI/AIGuardPawn.h"
#include "Utils/MyBlueprintFunctionLibrary.h"

// Sets default values
//Lab Week 7: Implement: Set up this Projectile's Collision Sphere, Projectile Sprite, and  Projectile Movement Component. Don't forget to Lock Axis to 2D
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	/** sphere collision  */
	//CREATE the SphereComponent
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");

	//CALL SetSphereRadius() on SphereComponent passing in: 4.0f
	SphereComponent->SetSphereRadius(20.0f);

	//CALL  SetCollisionProfileName() on SphereComponent, passing in: "BlockAll"
	SphereComponent->SetCollisionProfileName("BlockAll");

	//CALL AddDynamic() on SphereComponent->OnComponentHit passing in: this, &AProjectile::OnHit
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	//SphereComponent->BodyInstance.bLockYTranslation = true;
	
	//CALL UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis() passing in: SphereComponent . Have a look at this function and the UMyBlueprintFunctionLibrary class
	UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(SphereComponent);
	
	//SET the SphereComponent as the RootComponent
	SetRootComponent(SphereComponent);

	/** paper sprite component  */
	ProjectileSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("PaperFlipbookComponent"));
	ProjectileSprite->SetupAttachment(RootComponent);
	ProjectileSprite->SetRelativeLocation(FVector(-3.f, 0.f, 0.f));

	/** ProjectileMovementComponent  */
	//CREATE the ProjectileMovementComponent
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	//SET the ProjectileMovementComponent->UpdatedComponent to the SphereComponent
	ProjectileMovementComponent->UpdatedComponent = SphereComponent;
	
	//SET ProjectileMovementComponent->InitialSpeed to 1000.f
	ProjectileMovementComponent->InitialSpeed = 2000.0f;
	
	//SET ProjectileMovementComponent->MaxSpeed to 1000.f;
	ProjectileMovementComponent->MaxSpeed = 2000.0f;
	
	//SET ProjectileMovementComponent->bRotationFollowsVelocity to false
	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	
	//SET ProjectileMovementComponent->bShouldBounce to true
	ProjectileMovementComponent->bShouldBounce = true;
	

	/** projectiles not intended to live forever  */
	//SET InitialLifeSpan to 5.f. This sets the life span of this actor to 5 seconds. It will be destroyed after 5 seconds
	InitialLifeSpan = 5.0f;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}


//Lab Week 7 Implement: Destroy the Other Actor that has been Shot, 
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//COMMENT: Other Actor is the actor that triggered the event. Check that is not our self.
	//IF (OtherActor NOT EQUAL nullptr) AND (OtherActor NOT EQUAL this) AND (OtherComp NOT EQUAL nullptr) AND !IsPendingKill()
	if (OtherActor != nullptr)
	{
		//COMMENT: We don't want to destroy ourselves with our own projectile
		//IF OtherActor NOT EQUAL this->GetOwner()
        if (OtherActor != this->GetOwner())
		{
        	      //IF OtherActor->ActorHasTag("AIGuard") OR OtherActor->ActorHasTag("Player")
			if (OtherActor->ActorHasTag("AIGuard") || OtherActor->ActorHasTag("Player"))
			{
				//CALL Destroy() on OtherActor
				OtherActor->Destroy();
			}
        	      //ENDIF
		}
		//ENDIF
	}
	//ENDIF
}


