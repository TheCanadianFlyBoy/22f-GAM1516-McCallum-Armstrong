// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "Camera/CameraComponent.h"
#include "PaddlePawn.h"
#include "Brick.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

void MakeSideSolid(UBoxComponent* _side) {

	_side->SetSimulatePhysics(false);
	_side->SetEnableGravity(false);

	_side->GetBodyInstance()->bLockRotation = true;
	_side->GetBodyInstance()->bLockXRotation = true;
	_side->GetBodyInstance()->bLockYRotation = true;
	_side->GetBodyInstance()->bLockZRotation = true;
	_side->GetBodyInstance()->bLockTranslation = true;
	_side->GetBodyInstance()->bLockXTranslation = true;
	_side->GetBodyInstance()->bLockYTranslation = true;
	_side->GetBodyInstance()->bLockZTranslation = true;
	_side->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);
	_side->SetCollisionProfileName("BlockAll");
	_side->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	_side->SetNotifyRigidBodyCollision(true);

};

// Sets default values
ABoard::ABoard()
{

	boardWidth = 500; 
	boardHeight = 500;
	borderWidth = 50;
	//ROOT
	BoardRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = BoardRoot;



	//BOX COLLISION
	//Bottom Trigger Zone
	UBoxComponent* bottom = CreateDefaultSubobject<UBoxComponent>("BoardBottom");
	bottom->SetupAttachment(BoardRoot);
	bottom->SetBoxExtent(FVector(boardWidth, 50, borderWidth));
	bottom->AddLocalOffset(FVector(0, 0, -(boardHeight + borderWidth)));
	MakeSideSolid(bottom);
//bottom->SetSimulatePhysics(false);
//bottom->SetCollisionProfileName("OverlapAllDynamic");
//bottom->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//Add dynamics
	//bottom->OnComponentBeginOverlap.AddDynamic(this, &ABoard::BeginOverlap);
	//bottom->OnComponentEndOverlap.AddDynamic(this, &ABoard::EndOverlap);
	//Sides - LEFT //TODO REFACTOR TO FUNCTION?
	UBoxComponent* left = CreateDefaultSubobject<UBoxComponent>("BoardLeft");
	left->SetBoxExtent(FVector(borderWidth, 50, boardHeight));
	left->SetupAttachment(BoardRoot);
	left->AddLocalOffset(FVector(-(boardWidth + borderWidth), 0, 0));
	MakeSideSolid(left);
	//Sides - RIGHT
	UBoxComponent* right = CreateDefaultSubobject<UBoxComponent>("BoardRight");
	right->SetBoxExtent(FVector(borderWidth, 50, boardHeight));
	right->SetupAttachment(BoardRoot);
	right->AddLocalOffset(FVector((boardWidth + borderWidth), 0, 0));
	MakeSideSolid(right);

	//MakeSideSolid(right);
	//SIDES TOP
	UBoxComponent* top = CreateDefaultSubobject<UBoxComponent>("BoardTop");
	top->SetBoxExtent(FVector(boardWidth, 50, borderWidth));
	MakeSideSolid(top);
	top->SetupAttachment(BoardRoot);
	top->AddLocalOffset(FVector(0, 0, boardHeight + borderWidth));

	//CAMERA
	BoardCamera = CreateDefaultSubobject<UCameraComponent>("BoardCamera");
	BoardCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	BoardCamera->SetOrthoWidth(3000.0f);
	BoardCamera->SetAspectRatio(boardWidth / boardHeight); //TODO: figure out aspect ratio
	BoardCamera->SetupAttachment(BoardRoot);
	BoardCamera->AddLocalRotation(FRotator(0, -90, 0));
	BoardCamera->AddLocalOffset(FVector(-500, 0, 0));
	BoardCamera->bUsePawnControlRotation = false;

	BoxColliders.Add(top);
	BoxColliders.Add(bottom);
	BoxColliders.Add(left);
	BoxColliders.Add(right);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//GenerateBoard();
}


void ABoard::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ABoard::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABoard::SpawnPowerup(ABrick* _brick)
{
}

void ABoard::SpawnBall(APaddlePawn* _paddle)
{
}

// Called when the game starts or when spawned
void ABoard::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateBoard();

}

void ABoard::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

// Called every frame
void ABoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoard::GenerateBoard()
{
	//Generic brick count
	int brick_count = 5;
	//Dimensions
	float spawn_width = boardWidth*2 - 2 * borderWidth;
	float spawn_height = boardHeight / 2 - borderWidth;
	float max_bricks_x = spawn_width / 100;
	float max_bricks_y = spawn_height / 20;
	//Offset
	float z_offset = boardHeight/4 - borderWidth;

	//params
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	FTransform SpawnTransform = FTransform(GetActorLocation() - FVector(-boardWidth + borderWidth, 0, z_offset));
	
	//Brick Template catch
	if (BrickTemplate != nullptr) {
		while (brick_count > 0)
		{
			int row_number = FMath::RandRange(0, brick_count);
			row_number = FMath::Clamp(row_number, 1, (int) max_bricks_x);

			float row_borders = FMath::Fmod(spawn_width, (float) row_number);

			UWorld* World = GetWorld();

			for (int i = 0; i < row_number; i++)
			{
				//Get x offset
				float x_offset = (boardWidth*2/ ((float) row_number + 1));
				//Set new spawn transform
				FVector SpawnVector = GetActorLocation() - FVector(boardWidth,0,0) + FVector(x_offset * (i + 1), 0, z_offset);
				SpawnTransform = FTransform(SpawnVector);
				//Create new brick
				ABrick* _brick = World->SpawnActor<ABrick>(BrickTemplate, SpawnTransform, SpawnParams);
				if (_brick)
				{
					FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
				}

				brick_count--;

			}

			//Increment row height
			z_offset += 40;
		}
	}
}

