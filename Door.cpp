// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "Priceless/Core/MainCharacter.h"
#include "Priceless/Core/Room.h"
#include "PaperSprite.h"

// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Interactable/Door/Door_Texture_Sprite.Door_Texture_Sprite'")));
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetSprite(Sprite);
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetRelativeLocation({0,0,-16.0f});
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	// SetRootComponent(SpriteComponent);

	BoxCollision1 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision1"));
	BoxCollision1->SetupAttachment(SpriteComponent);
	BoxCollision1->SetBoxExtent({4,32,16});
	BoxCollision1->SetRelativeLocation({-1, 0, 16.0f});
	// BoxCollision1->SetHiddenInGame(false); // For Debug
	BoxCollision1->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision1->SetGenerateOverlapEvents(false);

	BoxCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision2"));
	BoxCollision2->SetupAttachment(RootComponent);
	BoxCollision2->SetBoxExtent({8,32,16});
	BoxCollision2->SetRelativeLocation({-4, 0, 0});
	BoxCollision2->SetCollisionResponseToAllChannels(ECR_Overlap);
	// BoxCollision2->SetHiddenInGame(false); // For Debug
	BoxCollision2->SetGenerateOverlapEvents(true);


	LightBlocker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightBlocker"));
	LightBlocker->SetupAttachment(BoxCollision1);
	LightBlocker->SetCollisionResponseToAllChannels(ECR_Ignore);
	LightBlocker->SetGenerateOverlapEvents(false);
	LightBlocker->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	LightBlocker->SetRelativeScale3D({0.075000f, 1.000000f, 0.320000f}); // Set Scale (X=0.075000,Y=1.000000,Z=0.320000)
	LightBlocker->SetRelativeLocation({1.500000f,0.000000f,0.000000f});
	LightBlocker->SetCastHiddenShadow(true); // Cast shadow while hidden in mame
	LightBlocker->bCastStaticShadow = false; // Don't cast Static Shadows
	LightBlocker->SetVisibility(false); // Set Invinsible
	LightBlocker->SetHiddenInGame(true); // Set Hidden in game

}

void ADoor::OpenDoor()
{
	SpriteComponent->SetRelativeRotation({-90,0,0}); // Открыть дверь
	DoorClosed = true;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetPawnOrSpectator()->DisableInput(PlayerController);
}

void ADoor::CloseDoor()
{
	SpriteComponent->SetRelativeRotation({0,0,0}); // Закрыть дверь
	DoorClosed = false;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->GetPawnOrSpectator()->EnableInput(PlayerController);
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADoor::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);
	// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s Interacted with %s"), *Caller->GetActorLabel(), *this->GetActorLabel()));
	if (DoorClosed)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
		//Binding the function with specific variables
		TimerDel.BindUFunction(this, FName("TeleportCharacter"), Caller);
		//Calling MyUsefulFunction after 1 seconds without looping
		GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 1.f, false);
		GetWorld()->GetTimerManager().SetTimer(DoorTimerHandle, this, &ADoor::CloseDoor, MaxDelayTime, false);
	}
}

bool ADoor::FindEndPointDoor()
{
	FVector Loc = GetActorLocation();
	FRotator Rot = GetActorRotation();
	FHitResult Hit;

	// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s"),*GetActorRotation().ToString()));
	float RotPitch = GetActorRotation().Pitch;
	float RotYaw = GetActorRotation().Yaw;
	float RotRoll = GetActorRotation().Roll;
	float LocX = 0;
	float LocZ = 0;

	if (RotPitch < 0 && RotRoll < 0) // Дверь снизу
	{
		Loc = {Loc.X, Loc.Y, Loc.Z - 32};
		LocZ = -32;
	}
	else if (RotPitch > 0 && RotRoll > 0) // Дверь Сверху
	{
		Loc = {Loc.X, Loc.Y, Loc.Z + 32};
		LocZ = 32;
	}
	else if (RotYaw < 0) // Дверь Слева
	{
		Loc = {Loc.X  -32, Loc.Y, Loc.Z};
		LocX = -32;
	}
	else if (RotRoll < 0) // Дверь Справа
	{
		Loc = {Loc.X + 32, Loc.Y, Loc.Z};
		LocX = 32;
	}
	
	const FVector Start = Loc;
	FVector End = Start + (Rot.Vector() * TraceDistance);
	
	FCollisionQueryParams TraceParams;
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);
	if (bHit)
	{
		// DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5,5,5),FColor::Red, false, 2.0f); //For Debug
		TeleportLoc = {Hit.Actor->GetActorLocation().X + LocX,10,Hit.Actor->GetActorLocation().Z + LocZ}; // Координаты телепортации
		return true;
	}
	// DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f); //For Debug
	return false;
}

void ADoor::TeleportCharacter(AActor* MainCharacter)
{
	// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Attempt Teleport")));
	if (FindEndPointDoor()) // Если Что-то есть за дверью
	{
		MainCharacter->SetActorLocation({TeleportLoc.X, MainCharacter->GetActorLocation().Y,TeleportLoc.Z}); // Телепортировать персонажа
	};
}


