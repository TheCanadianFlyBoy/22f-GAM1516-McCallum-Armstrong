// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter():
	ACharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = this->GetCapsuleComponent();
	CollisionComponent->SetSimulatePhysics(true);
	SetRootComponent(CollisionComponent);

	MovementComponent = this->GetCharacterMovement();
	MovementComponent->SetUpdatedComponent(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponent->SetupAttachment(RootComponent);

	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;



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
	MovementComponent->AddInputVector(GetActorForwardVector() * Value, true);
	//AddMovementInput(GetActorForwardVector(), Value, true);
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value, true);
}

void APlayerCharacter::LookUp(float Value)
{
	CameraComponent->AddLocalRotation(FRotator(Value, 0, 0));
}

void APlayerCharacter::LookRight(float Value)
{
	CameraComponent->AddLocalRotation(FRotator(0, Value, 0));
	
}

void APlayerCharacter::Fire()
{
}

void APlayerCharacter::Jump()
{
}

