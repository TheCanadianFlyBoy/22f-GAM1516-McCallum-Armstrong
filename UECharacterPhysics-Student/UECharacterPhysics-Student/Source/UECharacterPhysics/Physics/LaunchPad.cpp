// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetBoxExtent(FVector(75, 75, 50));
	RootComponent = OverlapComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);

	// Subscribe/Bind to Event
	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OverlapLaunchPad);

	//CREATE the AudioComponent
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	//SET bAutoActivate on the AudioComponent to false
	AudioComponent->bAutoActivate = false;
	//CALL SetRelativeLocation() on AudioComponent passing in FVector(0.0f, 0.0f, 0.0f)
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	//ATTACH the AudioComponent to the RootComponent
	AudioComponent->SetupAttachment(RootComponent);

	//CREATE the ParticleSystem
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	//ATTACH the ParticleSystem to the RootComponent
	ParticleSystem->SetupAttachment(RootComponent);

	//SET LaunchStrength to 1500
	LaunchStrength = 1500;
	//SET LaunchPitchAngle to 35.0f
	LaunchPitchAngle = 35.0f;

}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();

	//CALL SetSound() on AudioComponent passing in LaunchPadSound
	AudioComponent->SetSound(LaunchPadSound);
}

void ALaunchPad::OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Make rotator with our specified 'pitch' and convert to a direction vector * intensity

	//DECLARE a variable called LaunchDirection of type FRotator and assign it to the return value of GetActorRotation()
	FRotator LaunchDirection = GetActorRotation();
	//ADD LaunchPitchAngle to LaunchDirection.Pitch
	LaunchDirection.Pitch += LaunchPitchAngle;
	//DECLARE a variable called LaunchVelocity of type FVector and Assign it to LaunchDirection.Vector() * LaunchStrength
	FVector LaunchVelocity = LaunchDirection.Vector() * LaunchStrength;

	//CAST OtherActor to ACharacter and assign it to a variable called OtherCharacter
	ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	//IF OtherCharacter is not null
	if ( OtherCharacter)
	{
		// Launch Player! Both booleans give consistent launch velocity by ignoring the current player velocity
		//CALL LaunchCharacter() on OtherCharacter passing in LaunchVelocity, true, true
		OtherCharacter->LaunchCharacter(LaunchVelocity, true, true);

		// Spawn FX
		//CALL SetTemplate() on ParticleSystem passing in ActivateLaunchPadEffect
		ParticleSystem->SetTemplate(ActivateLaunchPadEffect);
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());

		//IF AudioComponent is not playing
		if (!AudioComponent->IsPlaying())
		{
			//CALL Play() on AudioComponent
			AudioComponent->Play();
		}
		//ENDIF
		
		//CALL UGameplayStatics::PlaySoundAtLocation() passing in GetWorld(), ImpactSound, GetActorLocation()
		//UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
	}
	//ENDIF
	
	// Did not overlap a player, so check if it's a physics simulating actor we can launch
	//ELSE IF OtherComp AND OtherComp->IsSimulatingPhysics()
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		//CALL AddImpulse() on OtherComp passing in LaunchVelocity, NAME_None, true
		OtherComp->AddImpulse(LaunchVelocity, NAME_None, true);

		// Spawn FX
		//CALL SetTemplate() on ParticleSystem passing in ActivateLaunchPadEffect
		ParticleSystem->SetTemplate(ActivateLaunchPadEffect);
		//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ActivateLaunchPadEffect, GetActorLocation());

		//IF AudioComponent is not playing
		if (!AudioComponent->IsPlaying())
		{
			//CALL Play() on AudioComponent
			AudioComponent->Play();
		}
		//ENDIF
		
		//CALL UGameplayStatics::PlaySoundAtLocation() passing in GetWorld(), ImpactSound, GetActorLocation()
		//UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
	}
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

