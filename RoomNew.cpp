// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomNew.h"
#include "Priceless/StaticObjects/Wall.h"
#include "Priceless/StaticObjects/LeftLowerAndRightUpperCorner.h"
#include "Priceless/StaticObjects/LeftUpperAndRightLowerCorner.h"
#include "Priceless/StaticObjects/ClosedWall1.h"
#include "Priceless/StaticObjects/ClosedWall2.h"
#include "Priceless/Interact/Door.h"

// Sets default values
ARoomNew::ARoomNew()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRootComponent); // Сделать корнем
	RootComponent->SetMobility(EComponentMobility::Movable); // Установить статическое движение

	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Fone_Sprite.Fone_Sprite'"))); // Поинтер на спрайт
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetSprite(Sprite); // Подставить спрайт в компонент
	SpriteComponent->SetupAttachment(RootComponent); // Присоединить к руту
	SpriteComponent->SetHiddenInGame(true); //Скрыто в игре
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteComponent->SetMobility(EComponentMobility::Movable);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->SetRelativeRotation(FVector(0.0f, -90.0f, 0.0f).Rotation());
	// SpringArmComponent->SetAbsolute(false, false, false);
	SpringArmComponent->TargetArmLength = ArmLenght;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->FieldOfView = 25.0f;
	CameraComponent->SetConstraintAspectRatio(true);
	CameraComponent->AspectRatio = 1;

	CharacterCheckCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CharacterCheckCollision"));
	CharacterCheckCollision->SetupAttachment(RootComponent);
	CharacterCheckCollision->SetBoxExtent({16.000000,100.000000,16.000000});
	CharacterCheckCollision->OnComponentBeginOverlap.AddDynamic( this, &ARoomNew::OnOverlapBegin );
	CharacterCheckCollision->OnComponentEndOverlap.AddDynamic( this, &ARoomNew::OnOverlapEnd );
	// CharacterCheckCollision->SetCollisionResponseToAllChannels(ECR_Block);
	CharacterCheckCollision->SetGenerateOverlapEvents(true);
	// CharacterCheckCollision->SetMobility(EComponentMobility::Static);

	CharacterFollowerForCamera = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CharacterFollowerForCamera"));
	CharacterFollowerForCamera->SetupAttachment(RootComponent);
	CharacterFollowerForCamera->SetGenerateOverlapEvents(false);
	CharacterFollowerForCamera->SetVisibility(false);
	CharacterFollowerForCamera->SetHiddenInGame(true);
	CharacterFollowerForCamera->SetCollisionResponseToAllChannels(ECR_Ignore);
	
	// SetCorners();
}

// Called when the game starts or when spawned
void ARoomNew::BeginPlay()
{
	Super::BeginPlay();
	bPreviewRoom = false;
	DeleteRoom();
	// CenterRoom();
	SpawnRoom(RoomHeight, RoomWidth);
}

void ARoomNew::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == static_cast<AMainCharacter*>(OtherActor) && OtherComp->GetClass()->GetDesc() == "SphereComponent")
	{
		UE_LOG(LogTemp, Warning, TEXT("Entered Room: %s, Overlaped: %s"), *this->GetName(), *OtherComp->GetClass()->GetDesc()); //For Debug
		ChangeCamera();
		bChangedCameraToCharacter = true;
	}
	// else if (OtherActor == static_cast<AMainCharacter*>(OtherActor))
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Entered Room: %s, Overlaped: %s"), *this->GetName(), *OtherComp->GetClass()->GetDesc()); //For Debug
	// }
}

void ARoomNew::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OtherActor == static_cast<AMainCharacter*>(OtherActor) && OtherComp->GetClass()->GetDesc() == "SphereComponent")
	{
		UE_LOG(LogTemp, Warning, TEXT("Exited Room: %s, Overlaped: %s"), *this->GetName(), *OtherComp->GetClass()->GetDesc()); //For Debug
		bChangedCameraToCharacter = false;
	}
	// else if (OtherActor == static_cast<AMainCharacter*>(OtherActor))
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Entered Room: %s, Overlaped: %s"), *this->GetName(), *OtherComp->GetClass()->GetDesc()); //For Debug
	// }
}

void ARoomNew::SpawnRoom(const int RoomHeightSpawn, const int RoomWidthSpawn)
{
	for(int m = 0; m < RoomHeightSpawn; m++) //Высота
	{
		for (int n = 0; n < RoomWidthSpawn; n++) //Ширина
		{
			RoomChildActors.Add(SpawnTile(n,m)); // Пол
			if (bSpawnCharacter && m ==  roundf(RoomHeightSpawn/2) && n == roundf(RoomWidthSpawn/2))
			{
				Location = GetActorLocation();
				// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s"), *location.ToString())); //For Debug
				Location.X = Location.X + (n * 32); //X - вправо/влево
				Location.Z = Location.Z + (m * 32); //Z - вверх/вниз
				Location.Y = 10; //Y - вперед назад
				// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s"), *location.ToString())); //For Debug
				Rotation = GetActorRotation();
				GetWorld()->SpawnActor(Character, &Location, &Rotation);
			}
			else if (m == 0 && n == 0) // Левый нижний угол
			{
				// Spawn Child
				UChildActorComponent* CornerLU1 = NewObject<UChildActorComponent>(this);
				CornerLU1->bEditableWhenInherited = true;
				CornerLU1->RegisterComponent();
				CornerLU1->SetChildActorClass(ALeftLowerAndRightUpperCorner::StaticClass());
				CornerLU1->CreateChildActor();
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				CornerLU1->SetRelativeLocation(Location);
				CornerLU1->SetRelativeRotation(Rotation);
				RoomChildActors.Add(CornerLU1);
			}
			else if (m == RoomHeightSpawn-1 && n == RoomWidthSpawn-1) // Правый верхний угол
				{
				// Spawn Child
				UChildActorComponent* CornerLU1 = NewObject<UChildActorComponent>(this);
				CornerLU1->bEditableWhenInherited = true;
				CornerLU1->RegisterComponent();
				CornerLU1->SetChildActorClass(ALeftLowerAndRightUpperCorner::StaticClass());
				CornerLU1->CreateChildActor();
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				Rotation.Pitch = 180;
				CornerLU1->SetRelativeLocation(Location);
				CornerLU1->SetRelativeRotation(Rotation);
				RoomChildActors.Add(CornerLU1);
				}
			else if (m == 0 && n == RoomWidthSpawn-1) // Правый нижний угол
			{
				// Spawn Child
				UChildActorComponent* CornerUL1 = NewObject<UChildActorComponent>(this);
				CornerUL1->bEditableWhenInherited = true;
				CornerUL1->RegisterComponent();
				CornerUL1->SetChildActorClass(ALeftUpperAndRightLowerCorner::StaticClass());
				CornerUL1->CreateChildActor();
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				Rotation.Pitch = 180;
				CornerUL1->SetRelativeLocation(Location);
				CornerUL1->SetRelativeRotation(Rotation);
				RoomChildActors.Add(CornerUL1);
			}
			else if (m == RoomHeightSpawn-1 && n == 0) // Левый верхний угол
			{
				// Spawn Child
				UChildActorComponent* CornerUL1 = NewObject<UChildActorComponent>(this);
				CornerUL1->bEditableWhenInherited = true;
				CornerUL1->RegisterComponent();
				CornerUL1->SetChildActorClass(ALeftUpperAndRightLowerCorner::StaticClass());
				CornerUL1->CreateChildActor();
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				CornerUL1->SetRelativeLocation(Location);
				CornerUL1->SetRelativeRotation(Rotation);
				RoomChildActors.Add(CornerUL1);
			}
			else if (m == 0) //Нижняя стена
			{
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				if (DownDoor && ((n == roundf((RoomWidthSpawn/2) + DownDoorOffset)) || ((n == roundf((RoomWidthSpawn/2)) - 1 + DownDoorOffset)) || (n == roundf((RoomWidthSpawn/2)) + 1 + DownDoorOffset))) // Дверной проем снизу))
					{
					RoomChildActors.Add(SpawnDownDoor(n, Location, Rotation, this));
					}
				else
				{
					Rotation.Pitch = 90;
					Rotation.Roll = 180;
					UChildActorComponent* Wall1 = NewObject<UChildActorComponent>(this);
					Wall1->bEditableWhenInherited = true;
					Wall1->RegisterComponent();
					Wall1->SetChildActorClass(AWall::StaticClass());
					Wall1->CreateChildActor();
					Wall1->SetRelativeLocation(Location);
					Wall1->SetRelativeRotation(Rotation);
					RoomChildActors.Add(Wall1);
				}
			}
			else if (n == 0) // Левая Стена
			{
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				if (LeftDoor && ((m == roundf((RoomHeightSpawn/2) + LeftDoorOffset)) || ((m == roundf((RoomHeightSpawn/2)) - 1 + LeftDoorOffset)) || (m == roundf((RoomHeightSpawn/2)) + 1 + LeftDoorOffset))) // Дверной проем слева)
				{
					RoomChildActors.Add(SpawnLeftDoor(m, Location, Rotation, this));
				}
				else
				{
					UChildActorComponent* Wall1 = NewObject<UChildActorComponent>(this);
					Wall1->bEditableWhenInherited = true;
					Wall1->RegisterComponent();
					Wall1->SetChildActorClass(AWall::StaticClass());
					Wall1->CreateChildActor();
					Wall1->SetRelativeLocation(Location);
					Wall1->SetRelativeRotation(Rotation);
					RoomChildActors.Add(Wall1);
				}
			}
			else if (m == RoomHeightSpawn - 1) // Верхняя стена
			{
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				if (TopDoor && ((n == roundf((RoomWidthSpawn/2) + TopDoorOffset)) || ((n == roundf((RoomWidthSpawn/2)) - 1 + TopDoorOffset)) || (n == roundf((RoomWidthSpawn/2)) + 1 + TopDoorOffset))) // Дверной проем сверху))
				{
					RoomChildActors.Add(SpawnTopDoor(n, Location, Rotation, this));
				}
				else
				{
					Rotation.Pitch = -90;
					Rotation.Yaw = 180;
					UChildActorComponent* Wall1 = NewObject<UChildActorComponent>(this);
					Wall1->bEditableWhenInherited = true;
					Wall1->RegisterComponent();
					Wall1->SetChildActorClass(AWall::StaticClass());
					Wall1->CreateChildActor();
					Wall1->SetRelativeLocation(Location);
					Wall1->SetRelativeRotation(Rotation);
					RoomChildActors.Add(Wall1);
				}
			}
			else if (n == RoomWidthSpawn - 1) // Правая стена
			{
				Location = GetActorLocation();
				Location.X = Location.X + (n * 32);
				Location.Z = Location.Z + (m * 32);
				Location.Y = Location.Y + 1;
				Rotation = GetActorRotation();
				
				if (RightDoor && ((m == roundf((RoomHeightSpawn/2) + RightDoorOffset)) || ((m == roundf((RoomHeightSpawn/2)) - 1 + RightDoorOffset)) || (m == roundf((RoomHeightSpawn/2)) + 1 + RightDoorOffset))) // Дверной проем справа
 				{
					RoomChildActors.Add(SpawnRightDoor(m, Location, Rotation, this));
				}
				else
				{
					Rotation.Pitch = 180;
					UChildActorComponent* Wall1 = NewObject<UChildActorComponent>(this);
					Wall1->bEditableWhenInherited = true;
					Wall1->RegisterComponent();
					Wall1->SetChildActorClass(AWall::StaticClass());
					Wall1->CreateChildActor();
					Wall1->SetRelativeLocation(Location);
					Wall1->SetRelativeRotation(Rotation);
					RoomChildActors.Add(Wall1);
				}
			}
		}
	}
}

UChildActorComponent* ARoomNew::SpawnTile(int X, int Z)
{
	// Spawn Child
	UChildActorComponent* FloorTile1 = NewObject<UChildActorComponent>(this);
	FloorTile1->bEditableWhenInherited = true;
	FloorTile1->RegisterComponent();
	switch (FloorTypeSelection)
	{
	case (EFloorType::Floor1):
		FloorTile1->SetChildActorClass(AFloorTile::StaticClass());
		break;
	case (EFloorType::Floor2):
		FloorTile1->SetChildActorClass(AFloorTile2::StaticClass());
		break;
	case (EFloorType::Floor3):
		FloorTile1->SetChildActorClass(AFloorTile3::StaticClass());
		break;
	case (EFloorType::Floor4):
		FloorTile1->SetChildActorClass(AFloorTile4::StaticClass());
		break;
	case (EFloorType::Floor5):
		FloorTile1->SetChildActorClass(AFloorTile5::StaticClass());
		break;
	default:
		FloorTile1->SetChildActorClass(AFloorTile::StaticClass());
		break;
	}
	
	FloorTile1->CreateChildActor();
	Location = GetActorLocation();
	Location.X = Location.X + (X * 32);
	Location.Z = Location.Z + (Z * 32);
	Rotation = GetActorRotation();
	FloorTile1->SetRelativeLocation(Location);
	FloorTile1->SetRelativeRotation(Rotation);
	return FloorTile1;
}

// Right Door
UChildActorComponent* ARoomNew::SpawnRightDoor(int m, FVector loc, FRotator rot, UObject* Outer) const
{
	if (m == roundf((RoomHeight/2)) + RightDoorOffset) // Если Дверь
	{
		loc.X = loc.X + 10;
		rot.Roll = 180;
		UChildActorComponent* Door1 = NewObject<UChildActorComponent>(Outer);
		// CornerLU1->bEditableWhenInherited = true;
		Door1->RegisterComponent();
		Door1->SetChildActorClass(ADoor::StaticClass());
		Door1->CreateChildActor();
		Door1->SetRelativeLocation(loc);
		Door1->SetRelativeRotation(rot);
		return Door1;
	}
	else if ((m == roundf((RoomHeight/2)) - 1 + RightDoorOffset)) // Ecли под дверью
	{
		UChildActorComponent* ClosedWall11 = NewObject<UChildActorComponent>(Outer);
		ClosedWall11->bEditableWhenInherited = true;
		ClosedWall11->RegisterComponent();
		ClosedWall11->SetChildActorClass(AClosedWall1::StaticClass());
		ClosedWall11->CreateChildActor();
		ClosedWall11->SetRelativeLocation(loc);
		ClosedWall11->SetRelativeRotation(rot);
		return ClosedWall11;
	}
	else if (m == roundf((RoomHeight/2)) + 1 + RightDoorOffset) // Если над дверью
	{
		rot.Pitch = 180;
		UChildActorComponent* ClosedWall21 = NewObject<UChildActorComponent>(Outer);
		ClosedWall21->bEditableWhenInherited = true;
		ClosedWall21->RegisterComponent();
		ClosedWall21->SetChildActorClass(AClosedWall2::StaticClass());
		ClosedWall21->CreateChildActor();
		ClosedWall21->SetRelativeLocation(loc);
		ClosedWall21->SetRelativeRotation(rot);
		return ClosedWall21;
	}
	return nullptr;
}
void ARoomNew::RightDoorOffsetClamp(float Rh)
{
	if (RightDoorOffset > floorf((Rh-3)/2))
	{
		RightDoorOffset = floorf((Rh-3)/2);
	}
	else if (RightDoorOffset < (ceilf((Rh-3)/2) * -1))
	{
		RightDoorOffset = ceilf((Rh-3)/2) * -1;
	}
}

// Left Door
UChildActorComponent* ARoomNew::SpawnLeftDoor(int m, FVector loc, FRotator rot, UObject* Outer) const
{
	if (m == roundf((RoomHeight/2)) + LeftDoorOffset) // Если Дверь
	{
		loc.X = loc.X - 10;
		rot.Yaw = 180;
		UChildActorComponent* Door1 = NewObject<UChildActorComponent>(Outer);
		Door1->bEditableWhenInherited = true;
		Door1->RegisterComponent();
		Door1->SetChildActorClass(ADoor::StaticClass());
		Door1->CreateChildActor();
		Door1->SetRelativeLocation(loc);
		Door1->SetRelativeRotation(rot);
		return Door1;
	}
	else if ((m == roundf((RoomHeight/2)) - 1 + LeftDoorOffset)) // Ecли под дверью
	{
		UChildActorComponent* ClosedWall21 = NewObject<UChildActorComponent>(Outer);
		ClosedWall21->bEditableWhenInherited = true;
		ClosedWall21->RegisterComponent();
		ClosedWall21->SetChildActorClass(AClosedWall2::StaticClass());
		ClosedWall21->CreateChildActor();
		ClosedWall21->SetRelativeLocation(loc);
		ClosedWall21->SetRelativeRotation(rot);
		return ClosedWall21;
	}
	else if (m == roundf((RoomHeight/2)) + 1 + LeftDoorOffset) // Если над дверью
	{
		rot.Pitch = 180;
		UChildActorComponent* ClosedWall11 = NewObject<UChildActorComponent>(Outer);
		ClosedWall11->bEditableWhenInherited = true;
		ClosedWall11->RegisterComponent();
		ClosedWall11->SetChildActorClass(AClosedWall1::StaticClass());
		ClosedWall11->CreateChildActor();
		ClosedWall11->SetRelativeLocation(loc);
		ClosedWall11->SetRelativeRotation(rot);
		return ClosedWall11;
	}
	return nullptr;
}
void ARoomNew::LeftDoorOffsetClamp(float Rh)
{
	if (LeftDoorOffset > floorf((Rh-3)/2))
	{
		LeftDoorOffset = floorf((Rh-3)/2);
	}
	else if (LeftDoorOffset < (ceilf((Rh-3)/2) * -1))
	{
		LeftDoorOffset = ceilf((Rh-3)/2) * -1;
	}
}

// Top Door
UChildActorComponent* ARoomNew::SpawnTopDoor(int n, FVector loc, FRotator rot, UObject* Outer) const
{
	if (n == roundf((RoomWidth/2)) + TopDoorOffset) // Если Дверь
		{
		rot.Pitch = 90;
		rot.Yaw = 180;
		loc.Z = loc.Z + 10;
		UChildActorComponent* Door1 = NewObject<UChildActorComponent>(Outer);
		Door1->bEditableWhenInherited = true;
		Door1->RegisterComponent();
		Door1->SetChildActorClass(ADoor::StaticClass());
		Door1->CreateChildActor();
		Door1->SetRelativeLocation(loc);
		Door1->SetRelativeRotation(rot);
		return Door1;
		}
	else if ((n == roundf((RoomWidth/2)) - 1 + TopDoorOffset)) // Ecли под дверью
		{
		rot.Pitch = 90;
		rot.Yaw = 180;
		UChildActorComponent* ClosedWall11 = NewObject<UChildActorComponent>(Outer);
		ClosedWall11->bEditableWhenInherited = true;
		ClosedWall11->RegisterComponent();
		ClosedWall11->SetChildActorClass(AClosedWall1::StaticClass());
		ClosedWall11->CreateChildActor();
		ClosedWall11->SetRelativeLocation(loc);
		ClosedWall11->SetRelativeRotation(rot);
		return ClosedWall11;
		}
	else if (n == roundf((RoomWidth/2)) + 1 + TopDoorOffset) // Если над дверью
		{
		rot.Pitch = -90;
		rot.Yaw = 180;
		UChildActorComponent* ClosedWall21 = NewObject<UChildActorComponent>(Outer);
		ClosedWall21->bEditableWhenInherited = true;
		ClosedWall21->RegisterComponent();
		ClosedWall21->SetChildActorClass(AClosedWall2::StaticClass());
		ClosedWall21->CreateChildActor();
		ClosedWall21->SetRelativeLocation(loc);
		ClosedWall21->SetRelativeRotation(rot);
		return ClosedWall21;
		}
	return nullptr;
}
void ARoomNew::TopDoorOffsetClamp(float RW)
{
	if (TopDoorOffset > floorf((RW-3)/2))
	{
		TopDoorOffset = floorf((RW-3)/2);
	}
	else if (TopDoorOffset < (ceilf((RW-3)/2) * -1))
	{
		TopDoorOffset = ceilf((RW-3)/2) * -1;
	}
}

// Down Door
UChildActorComponent* ARoomNew::SpawnDownDoor(int n, FVector loc, FRotator rot, UObject* Outer) const
{
	if (n == roundf((RoomWidth/2)) + DownDoorOffset) // Если Дверь
		{
		loc.Z = loc.Z -10;
		rot.Roll = 180;
		rot.Pitch = -90;
		UChildActorComponent* Door1 = NewObject<UChildActorComponent>(Outer);
		Door1->bEditableWhenInherited = true;
		Door1->RegisterComponent();
		Door1->SetChildActorClass(ADoor::StaticClass());
		Door1->CreateChildActor();
		Door1->SetRelativeLocation(loc);
		Door1->SetRelativeRotation(rot);
		return Door1;
		}
	else if ((n == roundf((RoomWidth/2)) - 1 + DownDoorOffset)) // Ecли под дверью
		{
		rot.Pitch = 90;
		rot.Yaw = 180;
		UChildActorComponent* ClosedWall21 = NewObject<UChildActorComponent>(Outer);
		ClosedWall21->bEditableWhenInherited = true;
		ClosedWall21->RegisterComponent();
		ClosedWall21->SetChildActorClass(AClosedWall2::StaticClass());
		ClosedWall21->CreateChildActor();
		ClosedWall21->SetRelativeLocation(loc);
		ClosedWall21->SetRelativeRotation(rot);
		return ClosedWall21;
		}
	else if (n == roundf((RoomWidth/2)) + 1 + DownDoorOffset) // Если над дверью
		{
		rot.Roll = 180;
		rot.Pitch = -90;
		UChildActorComponent* ClosedWall11 = NewObject<UChildActorComponent>(Outer);
		ClosedWall11->bEditableWhenInherited = true;
		ClosedWall11->RegisterComponent();
		ClosedWall11->SetChildActorClass(AClosedWall1::StaticClass());
		ClosedWall11->CreateChildActor();
		ClosedWall11->SetRelativeLocation(loc);
		ClosedWall11->SetRelativeRotation(rot);
		return ClosedWall11;
		}
	return nullptr;
}
void ARoomNew::DownDoorOffsetClamp(float RW)
{
	if (DownDoorOffset > floorf((RW-3)/2))
	{
		DownDoorOffset = floorf((RW-3)/2);
	}
	else if (DownDoorOffset < (ceilf((RW-3)/2) * -1))
	{
		DownDoorOffset = ceilf((RW-3)/2) * -1;
	}
}

// Move Room
void ARoomNew::CenterRoom()
{
	float ActorX = (static_cast<int>(GetActorLocation().X) / 32) * 32;
	float ActorZ = (static_cast<int>(GetActorLocation().Z) / 32) * 32;
	SetActorLocation({ActorX, 0,ActorZ});
	bCenterRoom = false;
}
void ARoomNew::MoveRoomLeft()
{
	bMoveRoomLeft = false;
	SetActorLocation({GetActorLocation().X - 32,GetActorLocation().Y,GetActorLocation().Z});
	CenterRoom();
}
void ARoomNew::MoveRoomRight()
{
	bMoveRoomRight = false;
	SetActorLocation({GetActorLocation().X + 32,GetActorLocation().Y,GetActorLocation().Z});
	CenterRoom();
}
void ARoomNew::MoveRoomUp()
{
	bMoveRoomUp = false;
	SetActorLocation({GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z + 32});
	CenterRoom();
}
void ARoomNew::MoveRoomDown()
{
	bMoveRoomDown = false;
	SetActorLocation({GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z - 32});
	CenterRoom();
}

void ARoomNew::ChangeCamera()
{
	GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(this, 0.1f,  VTBlend_Linear, 0.0f, false);
	// UE_LOG(LogTemp, Warning, TEXT("Changed Camera for Room")); //For Debug
	BAlreadyChangedCamera = true;
}

void ARoomNew::ComponentFollow(const AMainCharacter* Player)
{
	if (CharacterCheckCollision->IsOverlappingActor(Player))
	{
		float PlayerX = Player->GetActorLocation().X;
		float PlayerZ = Player->GetActorLocation().Z;
		CharacterFollowerForCamera->SetWorldLocation({PlayerX,0.0f,PlayerZ});
		if (bFollowComponentDefault)
		{
			bFollowComponentDefault = false;
		}
	}
	else
	{
		if (!bFollowComponentDefault)
		{
			CharacterFollowerForCamera->SetRelativeLocation({static_cast<float>((RoomWidth - 1) * 16), 0, static_cast<float>((RoomHeight - 1) * 16)});
			bFollowComponentDefault = true;
		}
	}
}

void ARoomNew::CameraFollow(const AMainCharacter* Player)
{
	if (CharacterCheckCollision->IsOverlappingActor(Player))
	{
		if (CharacterFollowerForCamera->GetRelativeLocation().X > SpringArmComponent->GetRelativeLocation().X) // Right
		{
			if (CharacterFollowerForCamera->GetRelativeLocation().X < RuCornerX)
			{
				SpringArmComponent->SetRelativeLocation({CharacterFollowerForCamera->GetRelativeLocation().X, 0.0f, SpringArmComponent->GetRelativeLocation().Z});
			}
			else
			{
				SpringArmComponent->SetRelativeLocation({RuCornerX, 0.0f, SpringArmComponent->GetRelativeLocation().Z});
			}
		}
		if (CharacterFollowerForCamera->GetRelativeLocation().X < SpringArmComponent->GetRelativeLocation().X) // Left
		{
			if (CharacterFollowerForCamera->GetRelativeLocation().X > LlCornerX)
			{
				SpringArmComponent->SetRelativeLocation({CharacterFollowerForCamera->GetRelativeLocation().X, 0.0f, SpringArmComponent->GetRelativeLocation().Z});
			}
			else
			{
				SpringArmComponent->SetRelativeLocation({LlCornerX, 0.0f, SpringArmComponent->GetRelativeLocation().Z});
			}
		}
		if (CharacterFollowerForCamera->GetRelativeLocation().Z > SpringArmComponent->GetRelativeLocation().Z) // Up
		{
			if (CharacterFollowerForCamera->GetRelativeLocation().Z < RuCornerZ)
			{
				SpringArmComponent->SetRelativeLocation({SpringArmComponent->GetRelativeLocation().X, 0.0f, CharacterFollowerForCamera->GetRelativeLocation().Z});
			}
			else
			{
				SpringArmComponent->SetRelativeLocation({SpringArmComponent->GetRelativeLocation().X, 0.0f, RuCornerZ});
			}
		}
		if (CharacterFollowerForCamera->GetRelativeLocation().Z < SpringArmComponent->GetRelativeLocation().Z) // Down
		{
			if (CharacterFollowerForCamera->GetRelativeLocation().Z > LlCornerZ)
			{
				SpringArmComponent->SetRelativeLocation({SpringArmComponent->GetRelativeLocation().X, 0.0f, CharacterFollowerForCamera->GetRelativeLocation().Z});
			}
			else
			{
				SpringArmComponent->SetRelativeLocation({SpringArmComponent->GetRelativeLocation().X, 0.0f, LlCornerZ});
			}
		}
		if (bCameraDefault)
		{
			bCameraDefault = false;
		}
	}
	else
	{
		if (!bCameraDefault)
		{
			SpringArmComponent->SetRelativeLocation({static_cast<float>((RoomWidth - 1) * 16), 0, static_cast<float>((RoomHeight - 1) * 16)});
			bCameraDefault = true;
		}
	}
}

void ARoomNew::SetCorners()
{
	if (static_cast<float>((RoomWidth - 4) * 32) < 96.0f)
	{
		RuCornerX = (RoomWidth - 1) * 16;
		LlCornerX = (RoomWidth - 1) * 16;
	}else
	{
		RuCornerX = static_cast<float>((RoomWidth - 4) * 32);
		LlCornerX = 96.0f; //64
	}
	if (static_cast<float>((RoomHeight - 4) * 32) < 96.0f)
	{
		RuCornerZ = (RoomHeight - 1) * 16;
		LlCornerZ = (RoomHeight - 1) * 16;
	}else
	{
		RuCornerZ = static_cast<float>((RoomHeight - 4) * 32);
		LlCornerZ = 96.0f; //64
	}
}

void ARoomNew::DeleteRoom()
{
	for (UChildActorComponent* Child : RoomChildActors)
	{
		Child->UnregisterComponent();
		Child->DestroyComponent();
	}
	RoomChildActors.Empty();
}

// Called every frame
void ARoomNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!BAlreadyChangedCamera)
	{
		if (IsOverlappingActor(static_cast<AMainCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())))
		{
			ChangeCamera();	
		}
	}
	ComponentFollow(static_cast<AMainCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()));
	CameraFollow(static_cast<AMainCharacter*>(GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()));
}

void ARoomNew::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	if (SpawnLoc != GetActorLocation())
	{
		bPreviewRoom = false;
		SpawnLoc = GetActorLocation();
	}
	const float FWidth = static_cast<float>(RoomWidth);
	const float FHeight = static_cast<float>(RoomHeight);
	SetCorners();
	SpriteComponent->SetRelativeLocation({(FWidth - 1) * 16, 0, (FHeight - 1) * 16});
	SpriteComponent->SetRelativeScale3D({FWidth, 1, FHeight});
	SpriteComponent->SetGenerateOverlapEvents(false);

 	CharacterCheckCollision->SetRelativeLocation({(FWidth - 1) * 16, 0, (FHeight - 1) * 16});
	CharacterCheckCollision->SetRelativeScale3D({FWidth, 1, FHeight});
	
	SpringArmComponent->SetRelativeLocation({(FWidth - 1) * 16, 0, (FHeight - 1) * 16});
	
	//Offset clamps
	RightDoorOffsetClamp(FHeight);
	LeftDoorOffsetClamp(FHeight);
	TopDoorOffsetClamp(FWidth);
	DownDoorOffsetClamp(FWidth);
	if (bCenterRoom)
	{
		CenterRoom();
	}
	if (bMoveRoomLeft)
	{
		MoveRoomLeft();
	}
	if (bMoveRoomRight)
	{
		MoveRoomRight();
	}
	if (bMoveRoomUp)
	{
		MoveRoomUp();
	}
	if (bMoveRoomDown)
	{
		MoveRoomDown();
	}
	SetActorLocation({GetActorLocation().X, 0, GetActorLocation().Z}, false, nullptr, ETeleportType::None);
	if (bPreviewRoom)
	{
		CenterRoom();
		for (UChildActorComponent* Child : RoomChildActors)
		{
			Child->UnregisterComponent();
			Child->DestroyComponent();
		}
		RoomChildActors.Empty();
		if (bSpawnCharacter)
		{
			bSpawnCharacter = false;
			SpawnRoom(RoomHeight, RoomWidth);
			bSpawnCharacter = true;
		}
		else
		{
			SpawnRoom(RoomHeight, RoomWidth);
		}
		SpriteComponent->SetVisibility(false);
	}
	else if (!bPreviewRoom)
	{
		DeleteRoom();
		SpriteComponent->SetVisibility(true);
	}
}