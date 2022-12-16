// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
//Components
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "InventoryComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
//References
#include "Weapon.h"
#include "DoomPlayerState.h"
#include "Interactable.h"
//Utils
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	//Add player tag
	Tags.Add("Player");
	Tags.Add("CanDamage");


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	CameraComponent->SetProjectionMode(ECameraProjectionMode::Perspective);
	CameraComponent->SetFieldOfView(90.f);
	CameraComponent->SetAspectRatio(1.7f);
	CameraComponent->bConstrainAspectRatio = true;
	CameraComponent->bUsePawnControlRotation = true;

	//Create empty inventory
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));

	//Create weapon component
	WeaponSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Component Location"));
	WeaponSocket->SetupAttachment(CameraComponent);
	WeaponSocket->AddLocalOffset(GetActorForwardVector() * 25.f - FVector(0,0,10.f), false);
	WeaponSocket->AddLocalRotation(FRotator(0.f, 90.f, 0.f));

	NoiseComponent = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));

	//Subscribe to damage
	this->OnTakeAnyDamage.AddDynamic(this, &APlayerCharacter::OnShot);

}

AWeapon* APlayerCharacter::GetCurrentWeapon()
{
	return InventoryComponent->GetCurrentWeapon();
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Give default weapon
	if (DefaultWeapon)
	{
		InventoryComponent->AddWeapon((AWeapon*)GetWorld()->SpawnActor(DefaultWeapon));
		ADoomPlayerState* State = Cast<ADoomPlayerState>(GetPlayerState());
		State->AddAmmo(EAmmoType::Light, 15.f);	//TODO, make variable
	}
}

//TODO move to player state
void APlayerCharacter::OnShot(AActor* DamagedActor, float DamageAmount, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageInstigator)
{
	//Controller null check
	if (MyController)
	{
		//Get state and update damage
		ADoomPlayerState* MyState = (ADoomPlayerState*)GetPlayerState();
		MyState->OnDamage(DamageAmount);

	}
}



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::MoveForward(float Value)
{

	ADoomPlayerState* MyState = (ADoomPlayerState*)GetPlayerState();

	if (Value != 0.f && !MyState->IsDead()) {
		AddMovementInput(GetActorForwardVector(), Value);
	}

}

void APlayerCharacter::MoveRight(float Value)
{
	ADoomPlayerState* MyState = (ADoomPlayerState*)GetPlayerState();

	if (Value != 0.f && !MyState->IsDead())
	{
		AddMovementInput(GetActorRightVector(), Value);
	}

}

void APlayerCharacter::NextWeapon()
{
	InventoryComponent->NextWeapon();
}

void APlayerCharacter::PreviousWeapon()
{
	InventoryComponent->PreviousWeapon();
}

void APlayerCharacter::Interact()
{
	//Ensure alive
	ADoomPlayerState* MyState = (ADoomPlayerState*)GetPlayerState();
	if (MyState->Health > 0) {
		//Fire a ray
		AActor* Actor = GetPickableActor_LineTraceSingleByChannel(ECollisionChannel::ECC_WorldDynamic);
		if (Actor && Actor->ActorHasTag("Interactable"))
		{
			AInteractable* Interactable = (AInteractable*)Actor;
			Interactable->OnInteract(this);
		}
	}

}

void APlayerCharacter::BeginFire()
{
	//Ensure alive
	ADoomPlayerState* MyState = (ADoomPlayerState*)GetPlayerState();
	if (MyState->Health > 0) {
		//Get weapon
		AWeapon* CurrentWeapon = InventoryComponent->GetCurrentWeapon(); 
		//Null check
		if (CurrentWeapon)
		{
			CurrentWeapon->BeginFireTimer();
		}
	}
}

void APlayerCharacter::EndFire()
{
	//Get weapon
	AWeapon* CurrentWeapon = InventoryComponent->GetCurrentWeapon();
	//Null check
	if (CurrentWeapon)
	{
		CurrentWeapon->EndFireTimer();
	}
}

void APlayerCharacter::Jump()
{
	if (GetCharacterMovement()->CanAttemptJump()) {
		GetCharacterMovement()->DoJump(false);
	}
}

void APlayerCharacter::Die()
{
	//Empty tags
	Tags.Empty();
	GetCharacterMovement()->SetActive(false);
}

AActor* APlayerCharacter::GetPickableActor_LineTraceSingleByChannel(ECollisionChannel CollisionChannel)
{
	
	FVector StartTrace = GetActorLocation(); // trace start is the camera location
	FVector Direction = CameraComponent->GetForwardVector();
	FVector EndTrace = StartTrace + Direction * 300.f; // and trace end is the camera location + an offset in the direction you are looking, the 300 is the distance at which it checks

	//Setup parameters
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);	//Ignore weapon
	TraceParams.AddIgnoredActor(this->GetOwner()); //Ignore weapon owner
	TraceParams.bTraceComplex = true;	//Complex collision
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	UWorld* World = GetWorld();
	World->LineTraceSingleByChannel(Hit, StartTrace, EndTrace, CollisionChannel, TraceParams); // simple trace function  ECC_PhysicsBody
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Yellow, false, 1, 0, 5.f);
	return Hit.GetActor();
	

	return nullptr;
}