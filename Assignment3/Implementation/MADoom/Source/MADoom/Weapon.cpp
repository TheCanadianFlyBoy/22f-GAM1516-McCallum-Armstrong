// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
//Components
#include "PaperFlipbookComponent.h"
#include "ExplosiveBarrel.h"
#include "Components/AudioComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
//References
#include "PlayerCharacter.h"
//Utils
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Sprite
	SpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	SpriteComponent->Stop();
	SpriteComponent->SetLooping(false);
	SpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpriteComponent->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
	//Audio
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->Sound = FireSound;
	//Noise component
	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Noise Emitter"));
	NoiseEmitter->bAutoActivate = true;

	//Set fire
	bCanFire = true; //TODO remove
	WeaponRange = 5000.f;

}

void AWeapon::Fire()
{
	//Play animation
	SpriteComponent->Play();
	AudioComponent->Play();

	ACharacter* ActorOwner = Cast<ACharacter>(GetOwner());
	ActorOwner->MakeNoise(1.0, ActorOwner, GetActorLocation());

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
			hit->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), GetOwner());
		}
	}

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeapon::BeginFireTimer()
{
	//If timer is not active, start it, and begin firing procedure
	if (!GetWorldTimerManager().IsTimerActive(WeaponTimerHandle))
	{
		Fire();
		GetWorldTimerManager().SetTimer(WeaponTimerHandle, this, &AWeapon::Fire, RateOfFire, true);
	}
}

void AWeapon::EndFireTimer()
{
	//Get remaining time
	float remaining = GetWorldTimerManager().GetTimerRemaining(WeaponTimerHandle);
	//Set final timer
	GetWorldTimerManager().ClearTimer(WeaponTimerHandle);
	GetWorldTimerManager().SetTimer(WeaponTimerHandle, remaining, false);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!SpriteComponent->IsPlaying()) SpriteComponent->SetPlaybackPositionInFrames(1, true);
}

void AWeapon::Equip(APlayerCharacter* Player)
{
	//If there is a sprite, make it visible
	if (SpriteComponent)
	{
		this->SetActorHiddenInGame(false);
	}

	//Set owner
	SetOwner(Player);

	//Attach to player
	AttachToComponent(Player->WeaponSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);


}

void AWeapon::Unequip()
{
	//Stop fire timer
	EndFireTimer();

	//If there is a sprite, make it visible
	if (SpriteComponent)
	{
		this->SetActorHiddenInGame(true);
	}
	//Get rid of owner
	SetOwner(NULL);
	//Detach
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}




//TODO refactor
bool AWeapon::GetPickableActor_LineTraceTestByChannel(ECollisionChannel CollisionChannel)
{
	bool hit = false;
	//if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;
		//Call SetupRay() to set the Start end End Trace
		SetupRay(StartTrace, Direction, EndTrace);
		FCollisionQueryParams TraceParams;
		//Ignore this Actor
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = true;

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		hit = World->LineTraceTestByChannel(StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 5.f);
		return hit;
	}

	return hit;
}

AActor* AWeapon::GetPickableActor_LineTraceSingleByChannel(ECollisionChannel CollisionChannel)
{
	//if (Controller && Controller->IsLocalPlayerController()) // we check the controller because we don't want bots to grab the use object and we need a controller for the GetPlayerViewpoint function
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
		World->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function  ECC_PhysicsBody
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 5.f);
		return Hit.GetActor();
	}

	return nullptr;
}

AActor* AWeapon::GetPickableActor_SphereTraceSingleByChannel(ECollisionChannel CollisionChannel)
{
	{

		FVector StartTrace;
		FVector Direction;
		FVector EndTrace;
		SetupRay(StartTrace, Direction, EndTrace);

		float Radius = 10.f;

		//Setup parameters
		FCollisionQueryParams TraceParams;
		SetupTraceParams(TraceParams);

		TArray<AActor*> IgnoredActors;
		IgnoredActors.Add(this);	//Ignore weapon
		IgnoredActors.Add(this->GetOwner()); //Ignore weapon owner

		FHitResult Hit(ForceInit);
		UWorld* World = GetWorld();
		UKismetSystemLibrary::SphereTraceSingle(GetWorld(), StartTrace, EndTrace, Radius, UEngineTypes::ConvertToTraceType(CollisionChannel), false, IgnoredActors, EDrawDebugTrace::ForDuration, Hit, true);
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, false, 1, 0, 5.f);
		return Hit.GetActor();
	}

	return nullptr;
}

TArray<FHitResult> AWeapon::GetPickableActor_LineTraceMultiByChannel(ECollisionChannel CollisionChannel)
{

	
	TArray<FHitResult> OutHits;
	//if (Controller && Controller->IsLocalPlayerController()) // we check the controller becouse we dont want bots to grab the use object and we need a controller for the Getplayerviewpoint function
	{
		//Create trace
		FVector StartTrace;
		FVector EndTrace;
		FVector Direction;
		SetupRay(StartTrace, Direction, EndTrace);

		//Params
		FCollisionQueryParams TraceParams;
		SetupTraceParams(TraceParams);

		//Get world
		UWorld* World = GetWorld();
		//Trace
		World->LineTraceMultiByChannel(OutHits, StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function ECC_PhysicsBody
		//Draw
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Green, true, 1, 0, 5.f);

	}

	return OutHits;
}

void AWeapon::SetupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace)
{
	StartTrace = GetActorLocation(); // trace start is the camera location
	Direction = GetActorRightVector() * -1;
	EndTrace = StartTrace + Direction * WeaponRange; // and trace end is the camera location + an offset in the direction you are looking, the 300 is the distance at which it checks
}

void AWeapon::SetupTraceParams(FCollisionQueryParams& TraceParams)
{
	TraceParams.AddIgnoredActor(this);	//Ignore weapon
	TraceParams.AddIgnoredActor(this->GetOwner()); //Ignore weapon owner
	TraceParams.bTraceComplex = true;	//Complex collision
	TraceParams.bReturnPhysicalMaterial = true;
}
