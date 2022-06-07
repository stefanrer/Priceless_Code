// Fill out your copyright notice in the Description page of Project Settings.

#include "Room.h"
#include "Engine/World.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRootComponent); // Сделать корнем
	RootComponent->SetMobility(EComponentMobility::Static); // Установить статическое движение

	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Fone_Sprite.Fone_Sprite'"))); // Поинтер на спрайт
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetSprite(Sprite); // Подставить спрайт в компонент
	SpriteComponent->SetupAttachment(RootComponent); // Присоединить к руту
	SpriteComponent->SetHiddenInGame(true); //Скрыто в игре
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteComponent->SetMobility(EComponentMobility::Static);
	
}

void ARoom::BeginPlay()
{
	Super::BeginPlay();
	for(int m = 0; m < RoomHeight; m++) //Высота
	{
		for (int n = 0; n < RoomWidth; n++) //Ширина
		{
			UWorld *World = GetWorld();
			SpawnTile(n,m); // Пол
			if (bSpawnCharacter && m ==  roundf(RoomHeight/2) && n == roundf(RoomWidth/2))
			{
				location = GetActorLocation();
				// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s"), *location.ToString())); //For Debug
				location.X = location.X + (n * 32); //X - вправо/влево
				location.Z = location.Z + (m * 32); //Z - вверх/вниз
				location.Y = 10; //Y - вперед назад
				// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s"), *location.ToString())); //For Debug
				rotation = GetActorRotation();
				World->SpawnActor(Character, &location, &rotation);
			}
			else if (m == 0 && n == 0) // Левый нижний угол
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32); //X - вправо/влево
				location.Z = location.Z + (m * 32); //Z - вверх/вниз
				location.Y = location.Y + 1; //Y - вперед назад
				rotation = GetActorRotation();
				World->SpawnActor(CornerLU, &location, &rotation);
			}
			else if (m == RoomHeight-1 && n == RoomWidth-1) // Правый верхний угол
				{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				rotation.Pitch = 180;
				World->SpawnActor(CornerLU, &location, &rotation);
				}
			else if (m == 0 && n == RoomWidth-1) // Правый нижний угол
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				rotation.Pitch = 180;	
				World->SpawnActor(CornerUL, &location, &rotation);
			}
			else if (m == RoomHeight-1 && n == 0) // Левый верхний угол
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				World->SpawnActor(CornerUL, &location, &rotation);
			}
			else if (m == 0) //Нижняя стена
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				if (DownDoor && ((n == roundf((RoomWidth/2) + DownDoorOffset)) || ((n == roundf((RoomWidth/2)) - 1 + DownDoorOffset)) || (n == roundf((RoomWidth/2)) + 1 + DownDoorOffset))) // Дверной проем снизу))
					{
					SpawnDownDoor(n, location, rotation);
					}
				else
				{
					rotation.Pitch = 90;
					rotation.Roll = 180;
					World->SpawnActor(Wall, &location, &rotation);
				}
			}
			else if (n == 0) // Левая Стена
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				if (LeftDoor && ((m == roundf((RoomHeight/2) + LeftDoorOffset)) || ((m == roundf((RoomHeight/2)) - 1 + LeftDoorOffset)) || (m == roundf((RoomHeight/2)) + 1 + LeftDoorOffset))) // Дверной проем слева)
				{
					SpawnLeftDoor(m, location, rotation);
				}
				else
				{
					World->SpawnActor(Wall, &location, &rotation);
				}
			}
			else if (m == RoomHeight - 1) // Верхняя стена
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				if (TopDoor && ((n == roundf((RoomWidth/2) + TopDoorOffset)) || ((n == roundf((RoomWidth/2)) - 1 + TopDoorOffset)) || (n == roundf((RoomWidth/2)) + 1 + TopDoorOffset))) // Дверной проем сверху))
				{
					SpawnTopDoor(n, location, rotation);
				}
				else
				{
					rotation.Pitch = -90;
					rotation.Yaw = 180;
					World->SpawnActor(Wall, &location, &rotation);
				}
			}
			else if (n == RoomWidth - 1) // Правая стена
			{
				location = GetActorLocation();
				location.X = location.X + (n * 32);
				location.Z = location.Z + (m * 32);
				location.Y = location.Y + 1;
				rotation = GetActorRotation();
				
				if (RightDoor && ((m == roundf((RoomHeight/2) + RightDoorOffset)) || ((m == roundf((RoomHeight/2)) - 1 + RightDoorOffset)) || (m == roundf((RoomHeight/2)) + 1 + RightDoorOffset))) // Дверной проем справа
 				{
					SpawnRightDoor(m, location, rotation);
				}
				else
				{
					rotation.Pitch = 180;
					World->SpawnActor(Wall, &location, &rotation);
				}
			}
		}
	}
	Destroy();
}
void ARoom::SpawnTile(int X, int Z)
{
	location = GetActorLocation();
	location.X = location.X + (X * 32);
	location.Z = location.Z + (Z * 32);
	rotation = GetActorRotation();
	UWorld *Wrld = GetWorld(); //Store Uworld object into a UWorld pointer, GetWorld() func returns the current UWorld object
	Wrld->SpawnActor(FloorTile, &location, &rotation);
}
void ARoom::RightDoorOffsetClamp()
{
	if (RightDoorOffset > floorf((RoomHeight-3)/2))
	{
		RightDoorOffset = floorf((RoomHeight-3)/2);
	}
	else if (RightDoorOffset < (ceilf((RoomHeight-3)/2) * -1))
	{
		RightDoorOffset = ceilf((RoomHeight-3)/2) * -1;
	}
}
void ARoom::LeftDoorOffsetClamp()
{
	if (LeftDoorOffset > floorf((RoomHeight-3)/2))
	{
		LeftDoorOffset = floorf((RoomHeight-3)/2);
	}
	else if (LeftDoorOffset < (ceilf((RoomHeight-3)/2) * -1))
	{
		LeftDoorOffset = ceilf((RoomHeight-3)/2) * -1;
	}
}
void ARoom::TopDoorOffsetClamp()
{
	if (TopDoorOffset > floorf((RoomWidth-3)/2))
	{
		TopDoorOffset = floorf((RoomWidth-3)/2);
	}
	else if (TopDoorOffset < (ceilf((RoomWidth-3)/2) * -1))
	{
		TopDoorOffset = ceilf((RoomWidth-3)/2) * -1;
	}
}
void ARoom::DownDoorOffsetClamp()
{
	if (DownDoorOffset > floorf((RoomWidth-3)/2))
	{
		DownDoorOffset = floorf((RoomWidth-3)/2);
	}
	else if (DownDoorOffset < (ceilf((RoomWidth-3)/2) * -1))
	{
		DownDoorOffset = ceilf((RoomWidth-3)/2) * -1;
	}
}
void ARoom::SpawnRightDoor(int m, FVector loc, FRotator rot) const
{
	UWorld *World = GetWorld();
	if (m == roundf((RoomHeight/2)) + RightDoorOffset) // Если Дверь
	{
		loc.X = loc.X + 10;
		rot.Roll = 180;
		World->SpawnActor(Door, &loc, &rot);
	}
	else if ((m == roundf((RoomHeight/2)) - 1 + RightDoorOffset)) // Ecли под дверью
	{
		World->SpawnActor(ClosedWall1, &loc, &rot);
	}
	else if (m == roundf((RoomHeight/2)) + 1 + RightDoorOffset) // Если над дверью
	{
		rot.Pitch = 180;
		World->SpawnActor(ClosedWall2, &loc, &rot);
	}
}
void ARoom::SpawnLeftDoor(int m, FVector loc, FRotator rot) const
{
	UWorld *World = GetWorld();
	if (m == roundf((RoomHeight/2)) + LeftDoorOffset) // Если Дверь
	{
		loc.X = loc.X - 10;
		rot.Yaw = 180;
		World->SpawnActor(Door, &loc, &rot);
	}
	else if ((m == roundf((RoomHeight/2)) - 1 + LeftDoorOffset)) // Ecли под дверью
	{
		World->SpawnActor(ClosedWall2, &loc, &rot);
	}
	else if (m == roundf((RoomHeight/2)) + 1 + LeftDoorOffset) // Если над дверью
	{
		rot.Pitch = 180;
		World->SpawnActor(ClosedWall1, &loc, &rot);
	}
}
void ARoom::SpawnTopDoor(int n, FVector loc, FRotator rot) const
{
	UWorld *World = GetWorld();
	if (n == roundf((RoomWidth/2)) + TopDoorOffset) // Если Дверь
		{
		rot.Pitch = 90;
		rot.Yaw = 180;
		loc.Z = loc.Z + 10;
		World->SpawnActor(Door, &loc, &rot);
		}
	else if ((n == roundf((RoomWidth/2)) - 1 + TopDoorOffset)) // Ecли под дверью
		{
		rot.Pitch = 90;
		rot.Yaw = 180;
		World->SpawnActor(ClosedWall1, &loc, &rot);
		}
	else if (n == roundf((RoomWidth/2)) + 1 + TopDoorOffset) // Если над дверью
		{
		rot.Pitch = -90;
		rot.Yaw = 180;
		World->SpawnActor(ClosedWall2, &loc, &rot);
		}
}
void ARoom::SpawnDownDoor(int n, FVector loc, FRotator rot) const
{
	UWorld *World = GetWorld();
	if (n == roundf((RoomWidth/2)) + DownDoorOffset) // Если Дверь
		{
		loc.Z = loc.Z -10;
		rot.Roll = 180;
		rot.Pitch = -90;
		World->SpawnActor(Door, &loc, &rot);
		}
	else if ((n == roundf((RoomWidth/2)) - 1 + DownDoorOffset)) // Ecли под дверью
		{
		rot.Pitch = 90;
		rot.Yaw = 180;
		World->SpawnActor(ClosedWall2, &loc, &rot);
		}
	else if (n == roundf((RoomWidth/2)) + 1 + DownDoorOffset) // Если над дверью
		{
		rot.Roll = 180;
		rot.Pitch = -90;
		World->SpawnActor(ClosedWall1, &loc, &rot);
		}
}
void ARoom::CenterRoom()
{
	float ActorX = (static_cast<int>(GetActorLocation().X) / 32) * 32;
	float ActorZ = (static_cast<int>(GetActorLocation().Z) / 32) * 32;
	SetActorLocation({ActorX, 0,ActorZ});
	bCenterRoom = false;
}
void ARoom::MoveRoomLeft()
{
	bMoveRoomLeft = false;
	SetActorLocation({GetActorLocation().X - 32,GetActorLocation().Y,GetActorLocation().Z});
	CenterRoom();
}
void ARoom::MoveRoomRight()
{
	bMoveRoomRight = false;
	SetActorLocation({GetActorLocation().X + 32,GetActorLocation().Y,GetActorLocation().Z});
	CenterRoom();
}
void ARoom::MoveRoomUp()
{
	bMoveRoomUp = false;
	SetActorLocation({GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z + 32});
	CenterRoom();
}
void ARoom::MoveRoomDown()
{
	bMoveRoomDown = false;
	SetActorLocation({GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z - 32});
	CenterRoom();
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	const float fWidth = static_cast<float>(RoomWidth);
	const float fHeight = static_cast<float>(RoomHeight);
	SpriteComponent->SetRelativeLocation({(fWidth - 1) * 16, 0, (fHeight - 1) * 16});
	SpriteComponent->SetRelativeScale3D({fWidth, 1, fHeight});
	SpriteComponent->SetGenerateOverlapEvents(false);
	//Offset clamps
	RightDoorOffsetClamp();
	LeftDoorOffsetClamp();
	TopDoorOffsetClamp();
	DownDoorOffsetClamp();
	if (bCenterRoom){CenterRoom();}
	if (bMoveRoomLeft){MoveRoomLeft();}
	if (bMoveRoomRight){MoveRoomRight();}
	if (bMoveRoomUp){MoveRoomUp();}
	if (bMoveRoomDown){MoveRoomDown();}
	SetActorLocation({GetActorLocation().X, 0, GetActorLocation().Z}, false, nullptr, ETeleportType::None);
}

