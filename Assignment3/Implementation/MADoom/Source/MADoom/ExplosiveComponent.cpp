// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveComponent.h"
//Components
#include "Components/SphereComponent.h"
//References
#include "GameFramework/PawnMovementComponent.h"

// Sets default values for this component's properties
UExplosiveComponent::UExplosiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	ExplosionRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Explosion Radius"));
	ExplosionRadius->SetSphereRadius(200.f);
	ExplosionRadius->SetCollisionProfileName("OverlapAll");
	ExplosionRadius->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ExplosionRadius->OnComponentBeginOverlap.AddDynamic(this, &UExplosiveComponent::OnBeginOverlap);
	ExplosionRadius->OnComponentEndOverlap.AddDynamic(this, &UExplosiveComponent::OnEndOverlap);
	// ...
}


// Called when the game starts
void UExplosiveComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UExplosiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UExplosiveComponent::Explode(float Damage, float Force)
{
	for (AActor* Actor : ActorsInRadius)
	{
		//Do damage
		Actor->TakeDamage(Damage, FDamageEvent(), GetOwner()->GetInstigatorController(), GetOwner()->GetOwner());
		//cast
		APawn* Pawn = dynamic_cast<APawn*>(Actor);
		//Null check
		if (Pawn && Force > 0)
		{
			//Pawn->GetMovementComponent()->AddRadialImpulse(GetOwner()->GetActorLocation(), ExplosionRadius->GetScaledSphereRadius(), Force, ERadialImpulseFalloff::RIF_Linear, true);
		}
	}
}


void UExplosiveComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("CanDamage"))
	{
		if (!ActorsInRadius.Contains(OtherActor))
		{
			ActorsInRadius.Add(OtherActor);
		}
	}
}

void UExplosiveComponent::OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("CanDamage"))
	{
		if (!ActorsInRadius.Contains(OtherActor))
		{
			ActorsInRadius.Remove(OtherActor);
		}
	}
}

void UExplosiveComponent::SetupAttachment(USceneComponent* Component)
{
	ExplosionRadius->SetupAttachment(Component);
}