// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Priceless/StaticObjects/FloorTile.h"
#include "Priceless/StaticObjects/Wall.h"
#include "Priceless/StaticObjects/LeftLowerAndRightUpperCorner.h"
#include "Priceless/StaticObjects/LeftUpperAndRightLowerCorner.h"
#include "Priceless/StaticObjects/ClosedWall1.h"
#include "Priceless/StaticObjects/ClosedWall2.h"
#include "Priceless/Interact/Door.h"
#include "MainCharacter.h"
#include "Room.generated.h"

UCLASS()
class PRICELESS_API ARoom : public AActor
{
	GENERATED_BODY()
	// Sets default values for this actor's properties
	ARoom();

// Компоненты	
protected: 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneRootComponent;

	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;

// Переменные используемые только в c++	
private: 
	
	FVector location;
	FRotator rotation;

// Здесь кого создаем	
public: 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<AFloorTile> FloorTile = AFloorTile::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<ALeftLowerAndRightUpperCorner> CornerLU = ALeftLowerAndRightUpperCorner::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<ALeftUpperAndRightLowerCorner> CornerUL = ALeftUpperAndRightLowerCorner::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<AWall> Wall = AWall::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<AClosedWall1> ClosedWall1 = AClosedWall1::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<AClosedWall2> ClosedWall2 = AClosedWall2::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<ADoor> Door  = ADoor::StaticClass();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<AMainCharacter> Character = AMainCharacter::StaticClass();
	
// Здесь параметры комнаты / Размер и тд		
public:
	//Высота комнаты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Room Size", meta=(ClampMin="3"))
	int RoomHeight = 3;
	//Ширина комнаты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Room Size", meta=(ClampMin="3"))
	int RoomWidth = 3;

// Здесь особенности комнаты / Двери и тд	
protected:

	//Центрировать комнату по сетке
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Move Room")
	bool bCenterRoom = false;
	//Сдвинуть комнату влево
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Move Room")
	bool bMoveRoomLeft = false;
	//Сдвинуть комнату вправо
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Move Room")
	bool bMoveRoomRight = false;
	//Сдвинуть комнату вверх
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Move Room")
	bool bMoveRoomUp = false;
	//Сдвинуть комнату вниз
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Move Room")
	bool bMoveRoomDown = false;
	
	
	//Спавнить персонажа?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Character")
	bool bSpawnCharacter = false;
	
	//Есть ли дверь справа?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|RightDoor") 
	bool RightDoor = false;
	//Смешенние от центра, + вверх, - вниз
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|RightDoor") 
	int RightDoorOffset = 0;

	//Есть ли дверь слева?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|LeftDoor") 
	bool LeftDoor = false;
	//Смешенние от центра, + вверх, - вниз
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|LeftDoor") 
	int LeftDoorOffset = 0;

	//Есть ли дверь сверху?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|TopDoor") 
	bool TopDoor = false;
	//Смешенние от центра, + вправо, - влево
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|TopDoor") 
	int TopDoorOffset = 0;

	//Есть ли дверь снизу?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|DownDoor") 
	bool DownDoor = false;
	//Смешенние от центра, + вправо, - влево
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Features|Door|DownDoor") 
	int DownDoorOffset = 0;

	
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnTile(int X, int Z);
	void RightDoorOffsetClamp();
	void LeftDoorOffsetClamp();
	void TopDoorOffsetClamp();
	void DownDoorOffsetClamp();
	void SpawnRightDoor(int m, FVector loc, FRotator rot) const;
	void SpawnLeftDoor(int m, FVector loc, FRotator rot) const;
	void SpawnTopDoor(int n, FVector loc, FRotator rot) const;
	void SpawnDownDoor(int n, FVector loc, FRotator rot) const;
	void CenterRoom();
	void MoveRoomLeft();
	void MoveRoomRight();
	void MoveRoomUp();
	void MoveRoomDown();

public:
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

};
