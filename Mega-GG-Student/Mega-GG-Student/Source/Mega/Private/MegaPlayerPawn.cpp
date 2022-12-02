// Fill out your copyright notice in the Description page of Project Settings.

#include "MegaPlayerPawn.h"

#include "Classes/PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/PaperSprite.h"
#include "ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "MegaGameModeBase.h"

#include "InventoryComponent.h"
#include "PickupActor.h"
#include "Weapon.h"
#include "MyBlueprintFunctionLibrary.h"

// Sets default values
AMegaPlayerPawn::AMegaPlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#pragma region CapsuleComponent
    //CREATE the CapsuleComponent
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
    //SET the Collision Profile Name to BlockAll in the CapsuleComponent
	CapsuleComponent->SetCollisionProfileName("BlockAll");
    //SET Notify Rigid Body Collisions to true on the CapsuleComponent
	CapsuleComponent->SetNotifyRigidBodyCollision(true);
    //SET Simulate Physics to true on the CapsuleComponent
	CapsuleComponent->SetSimulatePhysics(true);
    //CALL LockPhysicsTo2D on the CapsuleComponent using the function in UMyBlueprintFunctionLibrary
	UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(CapsuleComponent);
    //SET the CapsuleComponent as the RootComponent
	RootComponent = CapsuleComponent;
#pragma endregion CapsuleCOmponent will be new RootComponent

#pragma region PlayerSprite
	//Setup the Player Visual 
    //CREAT the PlayerSprite Component
	PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>("Player Sprite Component");
    //SET the Collision Profile Name to NoCOllision on the PlayerSprite
	PlayerSprite->SetCollisionProfileName("NoCollision");
    //SET the Collision Enabled to NoCollision on the PlayerSprite
	PlayerSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //SET Generate Overlap Events to false on the PlayerSprite
	PlayerSprite->SetGenerateOverlapEvents(false);
    //ATTACH the PlayerSprite to the RootComponent
	PlayerSprite->SetupAttachment(RootComponent);
#pragma endregion PlayerSprite Setup and Set it as the Root Component, It also performs the Blocking when it hits something. Does not report the collisions
#pragma region SpringArmComponent And Camera
	/** camera boom  */
    //CREATE the SpringArmComponent
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    //ATTACH the SpringArmComponent to the RootComponent
	SpringArmComponent->SetupAttachment(RootComponent);
    //SET the Inherit Pitch, Yaw and Roll values to false on the SpringArmComponent
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;
    //SET the Relative Rotation to -90.0f on the Yaw of the SpringArmComponent 
	SpringArmComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    //CREATE the FollowCamera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera Component");
    //SET the Projection Mode to Orthographic on the FollowCamera
	FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
    //SET the Ortho Width to 5000 on the FollowCamera
	FollowCamera->SetOrthoWidth(5000.0f);
    //ATTACH the FollowCamera to the SpringArmComponent
	FollowCamera->SetupAttachment(SpringArmComponent);
#pragma endregion SpringArmComponent SpringArm and Camera Component Setup


    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger"));
    SphereComponent->SetupAttachment(RootComponent);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    SphereComponent->SetCollisionProfileName("OverlapAll");


    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
    //SET the DirectionEnum to DE_Right
	DirectionEnum = EDirectionEnum::DE_Right;
}

// Called when the game starts or when spawned
void AMegaPlayerPawn::BeginPlay()
{
	Super::BeginPlay();

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

void AMegaPlayerPawn::NextWeapon()
{
    //if (CurrentWeapon)
    //{
    //    CurrentWeapon->UnEquip();
    //}
    //InventoryComponent->NextInventoryItem();
    //CurrentWeapon = Cast<AWeaponActor>( InventoryComponent->GetCurrentInventory());

    //if (CurrentWeapon)
    //{
    //    CurrentWeapon->Equip(this);
    //}

    EquipFromInventory(EInventoryDirection::NEXT);
}

void AMegaPlayerPawn::PrevWeapon()
{
    //if (CurrentWeapon)
    //{
    //    CurrentWeapon->UnEquip();
    //}
    //InventoryComponent->PreviousInventoryItem();
    //CurrentWeapon = Cast<AWeaponActor>(InventoryComponent->GetCurrentInventory());

    //if (CurrentWeapon)
    //{
    //    CurrentWeapon->Equip(this);
    //}
    EquipFromInventory(EInventoryDirection::PREV);
}

void AMegaPlayerPawn::PickupWeapon()
{
    //DECLARE a TArray of type AActor called overlappingActors
    TArray<AActor*> overlappingActors;
    //CALL GetOverlappingActors() function on the SphereComponent, passing in the overlappingActors TArray
    SphereComponent->GetOverlappingActors(overlappingActors);
    //FOR Each AActor in the overlappingActors TArray
    for (auto& actor : overlappingActors)
    {
        //IF the actor has the Tag "Ball"
        if (actor->ActorHasTag(FName("Pickup"))) {

            InventoryComponent->AddToInventory(Cast<APickupActor>( actor ));
        }
        //ENDIF the actor has the Tag "Ball"
    }
    //END FOR
}

void AMegaPlayerPawn::FireWeapon()
{
    if (CurrentWeapon)
        CurrentWeapon->Fire();
}

void AMegaPlayerPawn::PullWeaponTrigger()
{
    if (CurrentWeapon)
        CurrentWeapon->PullTrigger();
}

void AMegaPlayerPawn::ReleaseWeaponTrigger()
{
    if (CurrentWeapon)
        CurrentWeapon->ReleaseTrigger();
}

// Called every frame
void AMegaPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //IF MovementRight NOT EQUAL to 0
	if (MovementRight != 0)
	{
        //IF Movement Right is GREATER than 0
		if (MovementRight > 0)
		{
            //SET the Relative Rotation on the PlayerSprite to a ZeroRotator
			PlayerSprite->SetRelativeRotation(FRotator(FRotator::ZeroRotator));
            //SET the DirectionEnum to DE_Right
			DirectionEnum = EDirectionEnum::DE_Right;
		}
        //ENDIF

        //IF MovementRight is LESS than 0
		if (MovementRight < 0)
		{
            //SET the Relative Rotation on the PlayerSprite to 180
			PlayerSprite->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
            //SET the DirectionEnum to DE_Left
			DirectionEnum = EDirectionEnum::DE_Left;
		}
        //ENDIF

        //CALL AddForce on the CapsuleCOmponent's BodyInstance moving it on the Forward Direction * MovementRight * 40000
		CapsuleComponent->BodyInstance.AddForce(FVector(1.0f, 0.0f, 0.0f) * MovementRight * 45000000);  //GetActorForwardVector()
	}
    //ENDIF

    //IF bJump IS true
	if (bJump)
	{
        //CALL AddForce on the CapsuleCOmponent's BodyInstance moving it on the Up Direction * 40000
		CapsuleComponent->BodyInstance.AddForce(FVector(0.0f, 0.0f, 1.0f) * 100000000);
	}
    //ENDIF

}

// Called to bind functionality to input
void AMegaPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    //CALL BindAxis() on the PlayerInputComponent, Binding the MoveRight Input Axis to the MoveRight Function
	PlayerInputComponent->BindAxis("MoveRight", this, &AMegaPlayerPawn::MoveRight);

    //CALL BindAction() on the PlayerInputComponent, Binding the Jump Input Action to the MoveUp Function when pressed
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMegaPlayerPawn::MoveUp);
    //CALL BindAction() on the PlayerInputComponent, Binding the Jump Input Action to the MoveUp Function when released
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMegaPlayerPawn::MoveUp);

    PlayerInputComponent->BindAction("Pickup", IE_Pressed, this, &AMegaPlayerPawn::PickupWeapon);

    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, this, &AMegaPlayerPawn::NextWeapon);
    PlayerInputComponent->BindAction("PrevWeapon", IE_Pressed, this, &AMegaPlayerPawn::PrevWeapon);

    //PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, this, &AMegaPlayerPawn::FireWeapon);
    PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, this, &AMegaPlayerPawn::PullWeaponTrigger);
    PlayerInputComponent->BindAction("FireWeapon", IE_Released, this, &AMegaPlayerPawn::ReleaseWeaponTrigger);
}

void AMegaPlayerPawn::MoveRight(float value)
{
    //SET MovementRight to value
	MovementRight = value;
}

void AMegaPlayerPawn::MoveUp()
{
    //TOGGLE bJump
	bJump = !bJump;
}



void AMegaPlayerPawn::EquipFromInventory(EInventoryDirection dir)
{
    if (CurrentWeapon)
    {
        CurrentWeapon->UnEquip();
    }

    dir == EInventoryDirection::NEXT ? InventoryComponent->NextInventoryItem() : InventoryComponent->PreviousInventoryItem();
    CurrentWeapon = Cast<AWeaponActor>(InventoryComponent->GetCurrentInventory());

    if (CurrentWeapon)
    {
        CurrentWeapon->Equip(this);
    }

}