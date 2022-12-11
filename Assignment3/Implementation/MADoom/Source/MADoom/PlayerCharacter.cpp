// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

#include "InventoryComponent.h"
#include "Weapon.h"

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



}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Weapon sway

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.f) {
		AddMovementInput(GetActorForwardVector(), Value);
	}

}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}

}

void APlayerCharacter::LookUp(float Value)
{
	
}

void APlayerCharacter::LookRight(float Value)
{
	//CameraComponent->AddLocalRotation(FRotator(0, Value, 0));
	
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
	//TODO
}

void APlayerCharacter::BeginFire()
{
	//Get weapon
	AWeapon* CurrentWeapon = InventoryComponent->GetCurrentWeapon(); //TODO remove and add to persistent variable
	//Null check
	if (CurrentWeapon)
	{
		CurrentWeapon->BeginFireTimer();
	}
}

void APlayerCharacter::EndFire()
{
	//Get weapon
	AWeapon* CurrentWeapon = InventoryComponent->GetCurrentWeapon(); //TODO ^
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
