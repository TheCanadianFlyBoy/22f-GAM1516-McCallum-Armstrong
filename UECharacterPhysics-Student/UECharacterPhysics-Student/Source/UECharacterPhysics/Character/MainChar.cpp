// Fill out your copyright notice in the Description page of Project Settings.


#include "MainChar.h"
#include "PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

#include "Kismet/GameplayStatics.h"


AMainChar::AMainChar()
{
	// Make sure to only use Yaw from controller and ignore rest of rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	//Initialize camera and boom
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation( FRotator(0.f, -90.f, 0.f) );
	SpringArm->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	SpringArm->SetUsingAbsoluteRotation(true);
	CameraComponent->bUsePawnControlRotation = false;
	CameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.f, -1.f, 0.f));

	LowAttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("LowAttackBox"));
	LowAttackBox->SetupAttachment(GetSprite());
	LowAttackBox->SetCollisionProfileName("OverlapAll");
	LowAttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	HighAttackBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HighAttackBox"));
	HighAttackBox->SetupAttachment(GetSprite());
	HighAttackBox->SetCollisionProfileName("OverlapAll");
	HighAttackBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bIsAttacking = false;
	bCanBeDamaged = true;
	LastAttackAnimation = AttackAnimation_2;
	bIsAlive = true;
	bCanAttack = true;

	WeaponDelay = 0.65f;

}

void AMainChar::BeginPlay()
{
	Super::BeginPlay();

	LowAttackBox->OnComponentBeginOverlap.AddDynamic(this, &AMainChar::CombatOverlapBegin);
	LowAttackBox->OnComponentEndOverlap.AddDynamic(this, &AMainChar::CombatOverlapEnd);
	HighAttackBox->OnComponentBeginOverlap.AddDynamic(this, &AMainChar::CombatOverlapBegin);
	HighAttackBox->OnComponentEndOverlap.AddDynamic(this, &AMainChar::CombatOverlapEnd);

	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (controller)
	{
		FString command = "show collision";
		controller->ConsoleCommand(command, true);
		controller->bShowMouseCursor = true;
		controller->bEnableClickEvents = true;
		controller->bEnableMouseOverEvents = true;
	}
}

void AMainChar::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (bIsAlive) 
	{
		UpdateCharacter();
	}
	
}

void AMainChar::Jump()
{
	if (bIsAlive) 
	{
		Super::Jump();
	}
}

void AMainChar::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainChar::MoveRight);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainChar::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMainChar::Attack);
}

void AMainChar::MoveRight(float value)
{
	if (!bIsAttacking && bIsAlive && bCanBeDamaged) 
	{
		AddMovementInput(FVector(1.f, 0.f, 0.f), value*.4f);
	}
}

void AMainChar::UpdateCharacter()
{
	//1. Update Animation
	UpdateAnimation();
	//2. Setup Rotation of the controller based on direction
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;

	//3. Set rotation so that character faces direction of travel
	if (Controller != nullptr) 
	{
		if (TravelDirection < 0.f) 
		{
			Controller->SetControlRotation(FRotator(0.f, 180.f, 0.f));
		}
		else if (TravelDirection > 0.f) 
		{
			Controller->SetControlRotation(FRotator(0.f, 0.f, 0.f));
		}
	}

}

void AMainChar::UpdateAnimation()
{
	bool bIsFalling = GetMovementComponent()->IsFalling();
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	if (!bIsFalling) 
	{
		if (!bIsAttacking) 
		{
			if (bCanBeDamaged) 
			{
				UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.f) ? RunAnimation : IdleAnimation;
				if (GetSprite()->GetFlipbook() != DesiredAnimation) 
				{
					GetSprite()->SetFlipbook(DesiredAnimation);
				}
			}
		}
		else 
		{
			GetSprite()->SetFlipbook(LastAttackAnimation);
		}
	}
	else
	{
		if (GetSprite()->GetFlipbook() != JumpAnimation)
			GetSprite()->SetFlipbook(JumpAnimation);
	}
}

void AMainChar::Attack()
{
	bool bIsFalling = GetMovementComponent()->IsFalling();
	//We have to make sure we add a delay between attacks, so players can't just hack and slash their way out
	if (!bIsFalling && bIsAlive) 
	{
		if (!bIsAttacking && bCanAttack) 
		{
			LastAttackAnimation = LastAttackAnimation == AttackAnimation_1 ? AttackAnimation_2 : AttackAnimation_1;
			bIsAttacking = true; 
			if (LastAttackAnimation == AttackAnimation_1) 
			{
				ActivateCollision(LowAttackBox);
			}
			else 
			{
				ActivateCollision(HighAttackBox);
				bCanAttack = false;
			}
			GetWorldTimerManager().SetTimer(timerHandle, this, &AMainChar::EndAttack, 0.36f);
		}
	}
}

void AMainChar::EndAttack()
{
	bIsAttacking = false;
	if (LastAttackAnimation == AttackAnimation_1) 
	{
		DeactivateCollision(LowAttackBox);
	}
	else 
	{
		DeactivateCollision(HighAttackBox);
		GetWorldTimerManager().SetTimer(attackDelayHandle, this, &AMainChar::ResetWeaponDelay, WeaponDelay);
	}
}


void AMainChar::ResetWeaponDelay()
{
	bCanAttack = true;
}

void AMainChar::ActivateCollision(UBoxComponent* Comp)
{
	Comp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMainChar::DeactivateCollision(UBoxComponent* Comp)
{
	Comp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMainChar::CombatOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{

	}
}

void AMainChar::CombatOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{

	}
}
