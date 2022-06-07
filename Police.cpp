// Fill out your copyright notice in the Description page of Project Settings.


#include "Police.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APolice::APolice()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	SetRootComponent(FlipbookComponent);
	FlipbookComponent->SetFlipbook(IdleFlipbook);
	FlipbookComponent->SetEnableGravity(false);
	
	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash Light"));
	FlashLight->SetupAttachment(FlipbookComponent);
	FlashLight->SetRelativeLocation({5.0f,0.0f,5.0f});
	FlashLight->SetRelativeRotation({90.0f, 0.0f,0.0f});
	FlashLight->Intensity = 600.0f;
	FlashLight->LightColor = FColor::FromHex("FFD321FF");
	FlashLight->AttenuationRadius = 172.0f;
	FlashLight->InnerConeAngle = 20.0f;
	FlashLight->OuterConeAngle = 30.0f;
}

// Called when the game starts or when spawned
void APolice::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APolice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bPatrol)
	{
		if (bDoOnceMove)
		{
			FlipbookComponent->SetFlipbook(MoveFlipbook);
			bDoOnceMove = false;
			bDoOnceIdle = true;
		}
		Patrol(DeltaTime, bPatrolClock);
	}
	else
	{
		if (bDoOnceIdle)
		{
			FlipbookComponent->SetFlipbook(IdleFlipbook);
			bDoOnceIdle = false;
			bDoOnceMove = true;
		}
	}
}

auto APolice::CheckLeftObstacle() const -> bool
{
	FCollisionQueryParams TraceParams;
	FHitResult Hit;
	TArray<AActor*> IgnoreActors;
	FVector Loc = GetActorLocation();
	FRotator Rot = {-180, 0, 0};
	const FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);
	FVector Half_Size = {0.f, 0.f, Box_Width};
	FRotator Orientation = {0, 0, 0};


	bool bHit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End, Half_Size, Orientation, TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, LifeTime);
	return bHit;
}
auto APolice::CheckRightObstacle() const -> bool
{

	FCollisionQueryParams TraceParams;
	FHitResult Hit;
	TArray<AActor*> IgnoreActors;
	FVector Loc = GetActorLocation();
	FRotator Rot = {0, 0, 0};
	const FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);
	FVector Half_Size = {0.f, 0.f, Box_Width};
	FRotator Orientation = {0, 0, 0};
	
	bool bHit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End, Half_Size, Orientation, TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, LifeTime);
	return bHit;
}
auto APolice::CheckUpObstacle() const -> bool
{
	FCollisionQueryParams TraceParams;
	FHitResult Hit;
	TArray<AActor*> IgnoreActors;
	FVector Loc = GetActorLocation();
	FRotator Rot = {90, 0, 0};
	const FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);
	FVector Half_Size = {Box_Width, 0.f, 0.f};
	FRotator Orientation = {0, 0, 0};
	
	bool bHit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End, Half_Size, Orientation, TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, LifeTime);
	return bHit;
}
auto APolice::CheckDownObstacle() const -> bool
{
	FCollisionQueryParams TraceParams;
	FHitResult Hit;
	TArray<AActor*> IgnoreActors;
	FVector Loc = GetActorLocation();
	FRotator Rot = {-90, 0, 0};
	const FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);
	FVector Half_Size = {Box_Width, 0.f, 0.f};
	FRotator Orientation = {0, 0, 0};
	
	bool bHit = UKismetSystemLibrary::BoxTraceSingle(GetWorld(), Start, End, Half_Size, Orientation, TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::None, Hit, true, FLinearColor::Red, FLinearColor::Green, LifeTime);
	return bHit;
}

/**
 * @brief Switch Movement
 * @param State 0 - Left, 1 - Right, 2 - UP, 3 - Down
 * @param DeltaTime DeltaTime from Tick
 */
void APolice::PatrolMoveSwitch(const int State, const float DeltaTime)
{
	// UE_LOG(LogTemp, Warning, TEXT("State = %d"), State); //For Debug
	switch (State) {
		case 0: //Move Left
			{
				SetActorRotation({90, 0, 0});
				const FVector CurrentActorLoc = GetActorLocation();
				const FVector NewActorLoc = {CurrentActorLoc.X - FPatrolSpeed * DeltaTime, CurrentActorLoc.Y, CurrentActorLoc.Z};
				SetActorLocation(NewActorLoc);
				// UE_LOG(LogTemp, Warning, TEXT("Move Left")); //For Debug
				break;
			}
		case 1: //Move Right
			{
				SetActorRotation({-90,0,0});
				const FVector CurrentActorLoc = GetActorLocation();
				const FVector NewActorLoc = {CurrentActorLoc.X + FPatrolSpeed * DeltaTime, CurrentActorLoc.Y, CurrentActorLoc.Z};
				SetActorLocation(NewActorLoc);
				// UE_LOG(LogTemp, Warning, TEXT("Move Right")); //For Debug
				break;
			}
		case 2: //Move UP
			{
				SetActorRotation({0, 0, 0});
				const FVector CurrentActorLoc = GetActorLocation();
				const FVector NewActorLoc = {CurrentActorLoc.X, CurrentActorLoc.Y, CurrentActorLoc.Z + FPatrolSpeed * DeltaTime};
				SetActorLocation(NewActorLoc);
				// UE_LOG(LogTemp, Warning, TEXT("Move UP")); //For Debug
				break;;
			}
		case 3: // Move Down
			{
				SetActorRotation({-180, 0, 0});
				const FVector CurrentActorLoc = GetActorLocation();
				const FVector NewActorLoc = {CurrentActorLoc.X, CurrentActorLoc.Y, CurrentActorLoc.Z - FPatrolSpeed * DeltaTime};
				SetActorLocation(NewActorLoc);
				// UE_LOG(LogTemp, Warning, TEXT("Move Down")); //For Debug
				break;
			}
		default: //Don't Move
			{
				// UE_LOG(LogTemp, Warning, TEXT("Default")); //For Debug
			};
	}
}

void APolice::Patrol(float DeltaTime, bool bMovementDirection)
{
	const bool Left = CheckLeftObstacle();
	const bool Right = CheckRightObstacle();
	const bool UP = CheckUpObstacle();
	const bool Down = CheckDownObstacle();
	
	if (!bMovementDirection) // AntiClockwise movement
	{
		if (!Left && !Right && !UP && !Down)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 229")); //For Debug
			if (bLeftWall)
			{
				PatrolMoveSwitch(0, DeltaTime);
			}
			else if (bRightWall)
			{
				PatrolMoveSwitch(1, DeltaTime);
			}
			else if (bUPWall)
			{
				PatrolMoveSwitch(2, DeltaTime);
			}
			else if (bDownWall)
			{
				PatrolMoveSwitch(3, DeltaTime);
			}
			else
			{
				PatrolMoveSwitch(1, DeltaTime);
			}
			}
		else if (UP)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 253")); //For Debug
			if (!Left)
				{
				bUPWall = true;
				bDownWall = false;
				bLeftWall = false;
				bRightWall = false;
				PatrolMoveSwitch(0, DeltaTime);
				}
			else if (Left && !Down)
				{
				PatrolMoveSwitch(3, DeltaTime);
				}
			}
		else if (Left)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 270")); //For Debug
			if (!Down)
				{
				bLeftWall = true;
				bUPWall = false;
				bDownWall = false;
				bRightWall = false;
				PatrolMoveSwitch(3, DeltaTime);
				}
			else if (Down && !Right)
				{
				PatrolMoveSwitch(1, DeltaTime);
				}
			}
		else if (Down)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 286")); //For Debug
			if (!Right)
				{
				bDownWall = true;
				bLeftWall = false;
				bUPWall = false;
				bRightWall = false;
				PatrolMoveSwitch(1, DeltaTime);
				}
			else if (Right && !UP)
				{
				PatrolMoveSwitch(2, DeltaTime);
				}
			}
		else if (Right)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 302")); //For Debug
			if (!UP)
				{
				bRightWall = true;
				bDownWall = false;
				bLeftWall = false;
				bUPWall = false;
				PatrolMoveSwitch(2, DeltaTime);
				}
			else if (UP && !Left)
				{
				PatrolMoveSwitch(0, DeltaTime);
				}
			}
	} 
	else // Clockwise movement
	{
		if (!Left && !Right && !UP && !Down)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 321")); //For Debug
			if (bLeftWall)
			{
				PatrolMoveSwitch(0, DeltaTime);
			}
			else if (bRightWall)
			{
				PatrolMoveSwitch(1, DeltaTime);
			}
			else if (bUPWall)
			{
				PatrolMoveSwitch(2, DeltaTime);
			}
			else if (bDownWall)
			{
				PatrolMoveSwitch(3, DeltaTime);
			}
			else
			{
				PatrolMoveSwitch(0, DeltaTime);
			}
			}
		else if (UP)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 345")); //For Debug
			if (!Right)
				{
				bUPWall = true;
				bDownWall = false;
				bLeftWall = false;
				bRightWall = false;
				PatrolMoveSwitch(1, DeltaTime);
				}
			else if (Right && !Down)
				{
				PatrolMoveSwitch(3, DeltaTime);
				}
			}
		else if (Left)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 361")); //For Debug
			if (!UP)
				{
				bLeftWall = true;
				bUPWall = false;
				bDownWall = false;
				bRightWall = false;
				PatrolMoveSwitch(2, DeltaTime);
				}
			else if (UP && !Right)
				{
				PatrolMoveSwitch(1, DeltaTime);
				}
			}
		else if (Down)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 377")); //For Debug
			if (!Left)
				{
				bDownWall = true;
				bLeftWall = false;
				bUPWall = false;
				bRightWall = false;
				PatrolMoveSwitch(0, DeltaTime);
				}
			else if (Left && !UP)
				{
				PatrolMoveSwitch(2, DeltaTime);
				}
			}
		else if (Right)
			{
			// UE_LOG(LogTemp, Warning, TEXT("Line 393")); //For Debug
			if (!Down)
				{
				bRightWall = true;
				bDownWall = false;
				bLeftWall = false;
				bUPWall = false;
				PatrolMoveSwitch(3, DeltaTime);
				}
			else if (Down && !Left)
				{
				PatrolMoveSwitch(0, DeltaTime);
				}
			}
	}
}




