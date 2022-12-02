// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include <Components/SkeletalMeshComponent.h>
#include <Components/SphereComponent.h>
#include <Components/ArrowComponent.h>
#include "Net/UnrealNetwork.h"
#include "MegaPlayerPawn.h"
#include "Projectile.h"
#include "PaperSpriteComponent.h"

#include "Components/AudioComponent.h"
// Sets default values
AWeaponActor::AWeaponActor() 
	:Super()
{
	FireRate = 10.0f;
	MaximumAmmo = 300;
	CurrentAmmo = -1;
    Muzzle = CreateDefaultSubobject<UArrowComponent>("Muzzle");
    Muzzle->SetupAttachment(RootComponent);

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
    AudioComponent->bAutoActivate = false;
    AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    AudioComponent->SetupAttachment(RootComponent);
}

void AWeaponActor::Equip(class AMegaPlayerPawn* Character)
{
    Enable();
	verify(Character != nullptr && "Weapon's attach function called with null character!");

	// Set owner of this weapon.
	SetOwner(Character);

	// Attach weapon to the character's mesh.
	AttachToComponent(Character->PlayerSprite, FAttachmentTransformRules::SnapToTargetNotIncludingScale, "WeaponSocket");
}

void AWeaponActor::UnEquip()
{
    Disable();
	// Stop firing when the weapon is detached.
	ReleaseTrigger();

	// Unset owner of the weapon.
	SetOwner(nullptr);
	// Detach weapon from the character's mesh.
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}

void AWeaponActor::PullTrigger()
{
	auto& TimerManager = GetWorld()->GetTimerManager();

	// Check current ammo value before attempting to firing.
	if (CurrentAmmo > 0)
	{
		// Start the firing timer and use the remaining time of the previous timer.
		float RemainingTime = FMath::Max(TimerManager.GetTimerRemaining(FireTimer), 0.0f);
		TimerManager.SetTimer(FireTimer, this, &AWeaponActor::Fire, 1.0f / FireRate, true, RemainingTime);
	}
}

void AWeaponActor::ReleaseTrigger()
{
	auto& TimerManager = GetWorld()->GetTimerManager();

	// Replace timer with one that will prevent the primary fire timer from triggering again too quickly.
	if (TimerManager.TimerExists(FireTimer))
	{
		float RemainingTime = TimerManager.GetTimerRemaining(FireTimer);
		TimerManager.SetTimer(FireTimer, this, &AWeaponActor::ClearFireTimer, RemainingTime, false);
	}
}

FVector AWeaponActor::GetMuzzleLocation() const
{
	return Muzzle->GetComponentToWorld().GetLocation();
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//if (Sprite)
	//{
	//	Sprite->SetCollisionProfileName(FName("Custom"));
	//	Sprite->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//	Sprite->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);

	//}

	//// Get the muzzle arrow component.
	//auto Components = GetComponents();
	//for (auto Component : Components)
	//{
	//	if (Component->GetFName() == "Muzzle")
	//	{
	//		Muzzle = Cast<UArrowComponent>(Component);
	//		break;
	//	}
	//}
	//if (Muzzle)
	//{

	//}
	//check(Muzzle != nullptr && "Actor is mising an arrow component for muzzle!");

	// Sanitize default values.
	MaximumAmmo = FMath::Max(1, MaximumAmmo);
	CurrentAmmo = FMath::Min(CurrentAmmo, MaximumAmmo);

	// Set current ammo to maximum ammo.
	if (CurrentAmmo < 0)
	{
		CurrentAmmo = MaximumAmmo;
	}
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeaponActor::Fire()
{
    if (CurrentAmmo > 0)
    {
        if (!AudioComponent->IsPlaying()) {
            AudioComponent->SetSound(FireSound);
            AudioComponent->Play();
        }
        SpawnProjectile();
    }
}

void AWeaponActor::ClearFireTimer()
{
	// Clear the timer after a delay set in ReleaseTrigger() function.
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
}

void AWeaponActor::SpawnProjectile()
{
	
	{
		// Spawn a projectile.
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Owner = this;
		ActorSpawnParams.Instigator = Cast<APawn>(GetOwner()); 
		FTransform Transform = Muzzle->GetComponentTransform();
        AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Transform.GetLocation(), Transform.GetRotation().Rotator(), ActorSpawnParams);
        if (projectile)
        {
            FVector dir = FRotationMatrix(Transform.Rotator()).GetScaledAxis(EAxis::X);
            projectile->SetFireDirection(dir);
            //KickPower dir
           // ball->SphereCollision->BodyInstance.AddForce(1000000 * dir , NAME_None, true);
        }

		// Broadcast a weapon fired event.
		OnWeaponFired.Broadcast();

		// Decrement the ammo count.
		CurrentAmmo -= 1;
	}
	
}