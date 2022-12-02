// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
APlayerCharacter::APlayerCharacter():
	ACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = this->GetCapsuleComponent();
	CollisionComponent->SetSimulatePhysics(true);
	SetRootComponent(CollisionComponent);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	MovementComponent = this->GetCharacterMovement();
	MovementComponent->SetUpdatedComponent(RootComponent);
	MovementComponent->bConstrainToPlane = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;



}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	
}

void APlayerCharacter::LookUp(float Value)
{
	
}

void APlayerCharacter::LookRight(float Value)
{
	//CameraComponent->AddLocalRotation(FRotator(0, Value, 0));
	
}

void APlayerCharacter::Fire()
{
}

void APlayerCharacter::Jump()
{
}

