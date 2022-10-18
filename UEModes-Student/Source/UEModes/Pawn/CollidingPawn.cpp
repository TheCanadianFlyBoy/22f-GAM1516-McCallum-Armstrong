// Fill out your copyright notice in the Description page of Project Settings.


#include "CollidingPawn.h"
#include "PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

#pragma region Hierarchy 2
	//Collision Box
	PlayerRootCollisionBox = CreateDefaultSubobject<UBoxComponent>("SceneRoot");
	PlayerRootCollisionBox->SetSimulatePhysics(true);
	PlayerRootCollisionBox->SetCollisionProfileName("BlockAllDynamic");
	PlayerRootCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlayerRootCollisionBox->SetBoxExtent(FVector(135, 1, 150));
	//Rotational Locking
	PlayerRootCollisionBox->GetBodyInstance()->bLockXRotation = true;
	PlayerRootCollisionBox->GetBodyInstance()->bLockYRotation = true;
	PlayerRootCollisionBox->GetBodyInstance()->bLockZRotation = true;
	//Translational Locking
	PlayerRootCollisionBox->GetBodyInstance()->bLockYTranslation = true;

	SetRootComponent(PlayerRootCollisionBox);
	//OR
	//RootComponent = PlayerRoot;
	PawnSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("Pawn Sprite");
	PawnSpriteComponent->SetupAttachment(RootComponent);
	PawnSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 300.0f);
	SpringArm->TargetArmLength = 500.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.0f;
	SpringArm->bDoCollisionTest = false; //Disable Spring Arm Collision

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Pawns Camera");
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	FollowCamera->SetOrthoWidth(5000.0f);
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	
#pragma endregion Hierarchy 2	

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	NormalSpeed = 5;
	FastSpeed = 10;
	Speed = NormalSpeed;
}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	SetDirection(FVector::ForwardVector);
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    FVector NewLocation = GetActorLocation();
	//IF MovementForward NOT EQUAL to 0
	if (MovementForward != 0)
	{
	    //ASSIGN NewLocation to the the sum of the Actors Current Location and the product of the Actors Forward Vector and the MovementForward value i.e GetActorLocation() + (GetActorForwardVector() * MovementForward)
		NewLocation = GetActorLocation() + (GetActorForwardVector() * -MovementForward * Speed);
	}
	//ENDIF	

	//CALL SetActorLocation() passing in NewLocation
	SetActorLocation(NewLocation);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);

	PlayerInputComponent->BindAction("Speed", IE_Pressed, this, &ACollidingPawn::SpeedUp);
	PlayerInputComponent->BindAction("Speed", IE_Released, this, &ACollidingPawn::SlowDown);
}

void ACollidingPawn::SetDirection(const FVector Direction)
{
	if (Direction == FVector::ForwardVector) {
		PawnSpriteComponent->SetRelativeRotation(FRotator(0, 0, 0));
	}
	else if (Direction == FVector::BackwardVector) {
		PawnSpriteComponent->SetRelativeRotation(FRotator(0, 180, 0));
	}
}

void ACollidingPawn::MoveForward(float value)
{
	MovementForward = value;

	if (value > 0)
		SetDirection(FVector::BackwardVector);

	if (value < 0)
		SetDirection(FVector::ForwardVector);
}

void ACollidingPawn::SpeedUp()
{
	Speed = FastSpeed;
}

void ACollidingPawn::SlowDown()
{
	Speed = NormalSpeed;
}
