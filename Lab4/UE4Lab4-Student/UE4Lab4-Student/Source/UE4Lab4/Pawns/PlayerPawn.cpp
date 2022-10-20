// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerPawn.h"

#include "Classes/PaperSpriteComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/PaperSprite.h"
#include "ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"

#include "Projectile/Projectile.h"

#include "Utils/MyBlueprintFunctionLibrary.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
#pragma region CapsuleComponent
    //CREATE the CapsuleComponent
    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule Component");
    CapsuleComponent->SetCapsuleSize(60, 70);
	
    //SET the Collision Profile Name to BlockAll in the CapsuleComponent
    CapsuleComponent->SetCollisionProfileName("BlockAll");
	
    //SET Notify Rigid Body Collisions to true on the CapsuleComponent
    CapsuleComponent->SetNotifyRigidBodyCollision(true);
	
    //SET Simulate Physics to true on the CapsuleComponent
    CapsuleComponent->SetSimulatePhysics(true);

    //CALL SetLinearDamping() on the CapsuleComponent passing in 10. Play around with these values
    CapsuleComponent->SetLinearDamping(10.0f);
    
    //CALL SetAngularDamping() on the CapsuleComponent passing in 10. Play around with these values
    CapsuleComponent->SetAngularDamping(10.0f);
    
    //CALL LockPhysicsTo2D on the CapsuleComponent using the function in UMyBlueprintFunctionLibrary (Have a look at MyBlueprintFunctionLibrary.cpp)
    UMyBlueprintFunctionLibrary::LockPhysicsTo2DAxis(CapsuleComponent);
    
    //CALL AddDynamic() on CapsuleComponent->OnComponentHit passing in: this, &APlayerPawn::HandleBoxHit
    CapsuleComponent->OnComponentHit.AddDynamic(this, &APlayerPawn::HandleBoxHit);

    //SET the CapsuleComponent as the RootComponent
    SetRootComponent(CapsuleComponent);

#pragma endregion CapsuleCOmponent will be new RootComponent

#pragma region PlayerSprite
    //COMMENT: Setup the Player Visual 
    //CREATE the PlayerSprite Component
    PlayerSprite = CreateDefaultSubobject<UPaperSpriteComponent>("PlayerSprite");

    //SET the Collision Profile Name to NoCollision on the PlayerSprite
    PlayerSprite->SetCollisionProfileName("NoCollision");

    //SET the Collision Enabled to NoCollision on the PlayerSprite
    PlayerSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    //SET Generate Overlap Events to false on the PlayerSprite. Look up the SetGenerateOverlapEvents() function in the documentation
    PlayerSprite->SetGenerateOverlapEvents(false);

    //ATTACH the PlayerSprite to the RootComponent
    PlayerSprite->SetupAttachment(RootComponent);

#pragma endregion PlayerSprite Setup and Set it as the Root Component, It also performs the Blocking when it hits something. Does not report the collisions
#pragma region SpringArmComponent And Camera
     /** COMMENT: camera boom  */
    //CREATE the SpringArmComponent
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");

    //ATTACH the SpringArmComponent to the RootComponent
    SpringArmComponent->SetupAttachment(RootComponent);

    //SET the Inherit Pitch, Yaw and Roll values to false on the SpringArmComponent
    SpringArmComponent->bInheritPitch = false;
    SpringArmComponent->bInheritYaw = false;
    SpringArmComponent->bInheritRoll = false;

    //SET the Relative Rotation to -90.0f on the Yaw of the SpringArmComponent 
    SpringArmComponent->SetRelativeRotation(FRotator(0, -90.0f, 0));

    //CREATE the FollowCamera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");

    //SET the Projection Mode to Orthographic on the FollowCamera
    FollowCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);

    //SET the Ortho Width to 5000 on the FollowCamera
    FollowCamera->SetOrthoWidth(5000.0f);

    //ATTACH the FollowCamera to the SpringArmComponent
    FollowCamera->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

#pragma endregion SpringArmComponent SpringArm and Camera Component Setup
	
    /**COMMENT: projectile spawn point  */
    //CREATE the ProjectileSpawnPoint
    ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>("ProjectileSpawnPoint");

    //ATTACH the ProjectileSpawnPoint to the PlayerSprite
    ProjectileSpawnPoint->SetupAttachment(PlayerSprite);

    //CALL SetRelativeLocation() on ProjectileSpawnPoint passing in: FVector(40.f, 0.f, 30.f)
    ProjectileSpawnPoint->SetRelativeLocation(FVector(40.f, 0.f, 30.f));

    //CALL Add() on Tags (This is a variable in AActor), passing in: "Player". A tag is a label, so we can label this Actor with multiple tags  
    Tags.Add("Player");

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
//Lab Week 7 Implement: Set Can Shoot, and Start the SetCanShootTimer
void APlayerPawn::BeginPlay()
{
    Super::BeginPlay();

    //COMMENT: DON't Forget to set bCanShoot
    //SET bCanShoot to true
    SetCanShoot();


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

//Lab Week 7 Implement: Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
     Super::Tick(DeltaTime);

     //IF MovementRight NOT EQUAL to 0
     if (MovementRight != 0)
     {
        //IF Movement Right is GREATER than 0
         if (MovementRight > 0)
		{
            //SET the Relative Rotation on the PlayerSprite to a ZeroRotator
             PlayerSprite->SetRelativeRotation(FRotator(0,0,0));
		}
        //ENDIF

        //IF MovementRight is LESS than 0
         if (MovementRight < 0)
		{
            //SET the Relative Rotation on the PlayerSprite to 180
             PlayerSprite->SetRelativeRotation(FRotator(0, 180, 0));
		}
        //ENDIF

        //CALL AddForce() on the CapsuleComponent's BodyInstance moving it on the Forward Direction * MovementRight * 1000000.0f
         CapsuleComponent->BodyInstance.AddForce(GetActorForwardVector() * MovementRight * 1000000.0f);
     }
    //ENDIF

    
    //ENDIF

}

//Lab Week 7 Implement: Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //CALL BindAxis() on the PlayerInputComponent, Binding the MoveRight Input Axis to the MoveRight Function
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerPawn::MoveRight);

    //CALL BindAction() on the PlayerInputComponent, Binding the Jump Input Action to the Jump Function when pressed
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerPawn::Jump);

    //CALL BindAction() on the PlayerInputComponent, Binding the Fire Input Action to the SpawnProjectile Function when pressed
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerPawn::SpawnProjectile);

}

//Lab Week 7 Implement: Movement
void APlayerPawn::MoveRight(float value)
{
    //SET MovementRight to value
    MovementRight = value;
}

//Lab Week 7 Implement: Player pawn Jump 
void APlayerPawn::Jump()
{
    //IF bOnFloor IS true
    if (bOnFloor)
    {
    	//SET bOnFloor to false
        bOnFloor = false;
    	//CALL AddForce() on CapsuleComponent->BodyInstance passing in: FVector(0.0f, 0.0f, 1.0f) * 800000.0f * 40.0f
        CapsuleComponent->BodyInstance.AddForce(FVector(0.0f, 0.0f, 1.0f) * 2000000.0f * 40.0f);
    }
    //ENDIF
}

//Lab Week 7 Implement: Spawn the Projectile, 
void APlayerPawn::SpawnProjectile()
{
    //IF ProjectileTemplate NOT EQUAL to nullptr
    if (ProjectileTemplate != nullptr)
    {
    	//CREATE a variable called World of  UWorld* and assign it to the return value of GetWorld()
        UWorld* World = GetWorld();
    	//IF World != nullptr
        if (World != nullptr)
        {
        	//IF bCanShoot IS true
            if (bCanShoot)
            {
            	//SET bCanShoot to false
                bCanShoot = false;
            	//DECLARE a variable called SpawnParams of type FActorSpawnParameters
                FActorSpawnParameters SpawnParams;
            	//SET  SpawnParams.Owner to this
                SpawnParams.Owner = this;
            	//SET  SpawnParams.Instigator to the return value of GetInstigator()
                SpawnParams.Instigator = GetInstigator();
            	//SET SpawnParams.SpawnCollisionHandlingOverride to ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
            	//DECLARE a variable called SpawnLocation of type FVector and assign it to the return value of  GetProjectileSpawnPoint()->GetComponentLocation()
                FVector SpawnLocation = GetProjectileSpawnPoint()->GetComponentLocation();
            	//DECLARE a variable called SpawnRotation of type FRotator and assign it to the return value of GetProjectileSpawnPoint()->GetComponentRotation()
                FRotator SpawnRotation = GetProjectileSpawnPoint()->GetComponentRotation();

            	//DECLARE a variable called SpawnedProjectile of type AProjectile* and assign it to the return value of  World->SpawnActor<AProjectile>() passing in: ProjectileTemplate, SpawnLocation, SpawnRotation, SpawnParams
                AProjectile* SpawnedProjectile = World->SpawnActor<AProjectile>(ProjectileTemplate, SpawnLocation, SpawnRotation, SpawnParams);
            	//IF SpawnedProjectile NOT EQUAL to nullptr
                if (SpawnedProjectile != nullptr)
                {
                    //CALL AddOnScreenDebugMessage() on GEngine passing in: -1, 15.0f, FColor::Blue, "Spawn Projectile"
                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Spawn Projectile");
                    //CALL SetLifeSpan() on SpawnedProjectile passing in: ProjectileLifeSpan
                    SpawnedProjectile->SetLifeSpan(ProjectileLifeSpan);
                    //CALL GetWorldTimerManager().SetTimer() passing in: SetCanShootTimer, this, &APlayerPawn::SetCanShoot, FireTimerDelay, false
                    GetWorldTimerManager().SetTimer(SetCanShootTimer, this, &APlayerPawn::SetCanShoot, FireTimerDelay, false);
                }
            	//ENDIF
            }
        	//ENDIF
        }
    	//ENDIF
    }
    //ELSE
    
    {
    
    }
    //ENDIF
}

//Lab Week 7 Implement: Set that we Can Shoot
void APlayerPawn::SetCanShoot()
{
    //SET bCanShoot to true
    bCanShoot = true;
    
}

//Lab Week 7 Implement: Handle collision
void APlayerPawn::HandleBoxHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    //IF OtherActor NOT EQUAL to nullptr
    if (OtherActor != nullptr)
    
    {
    	//IF OtherActor->ActorHasTag("Floor")
        if (OtherActor->ActorHasTag("Floor"))
        {
            //SET bOnFloor to true
            bOnFloor = true;
        }
    	//ENDIF
    }
    //ENDIF
}
