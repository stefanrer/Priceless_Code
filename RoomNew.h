// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Priceless/StaticObjects/FloorTile.h"
#include "Priceless/StaticObjects/FloorTile2.h"
#include "Priceless/StaticObjects/FloorTile3.h"
#include "Priceless/StaticObjects/FloorTile4.h"
#include "Priceless/StaticObjects/FloorTile5.h"
#include "Components/BoxComponent.h"
#include "MainCharacter.h"
#include "Priceless/Core/EnumName.h"
#include "Priceless/Core/MainCharacter.h"
#include "RoomNew.generated.h"


UCLASS()
class PRICELESS_API ARoomNew : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoomNew();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneRootComponent;

	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;
	UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;
	UPROPERTY(Category = SpringArm, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ArmLenght = 500;
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* CharacterCheckCollision;
	UPROPERTY(Category = FollowComponent, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* CharacterFollowerForCamera;
	UPROPERTY()
	TArray<UChildActorComponent*> RoomChildActors;
	UPROPERTY()
	FVector SpawnLoc;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomSettings|Spawn Actor Setup")
	TEnumAsByte<EFloorType> FloorTypeSelection = EFloorType::Floor1;
	UPROPERTY(VisibleAnywhere, Category = "RoomSettings")
	float RuCornerX;
	UPROPERTY(VisibleAnywhere, Category = "RoomSettings")
	float RuCornerZ;
	UPROPERTY(VisibleAnywhere, Category = "RoomSettings")
	float LlCornerX;
	UPROPERTY(VisibleAnywhere, Category = "RoomSettings")
	float LlCornerZ;
private:

	FVector Location;
	FRotator Rotation;

	UPROPERTY()
	float BAlreadyChangedCamera = false;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Spawn Actor Setup")
	TSubclassOf<AMainCharacter> Character = AMainCharacter::StaticClass();
	
// Здесь параметры комнаты / Размер и тд		
public:
	//Высота комнаты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Room Size", meta=(ClampMin="5"))
	int RoomHeight = 5;
	//Ширина комнаты
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings|Room Size", meta=(ClampMin="5"))
	int RoomWidth = 5;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "RoomSettings")
	bool bPreviewRoom = false;

	UPROPERTY()
	bool bChangedCameraToCharacter = false;
	UPROPERTY()
	bool bFollowComponentDefault = false;
	UPROPERTY()
	bool bCameraDefault = false;
	
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
	void SpawnRoom(const int RoomHeightSpawn, const int RoomWidthSpawn);
	UChildActorComponent* SpawnTile(int X, int Z);
	void RightDoorOffsetClamp(float Rh);
	void LeftDoorOffsetClamp(float Rh);
	void TopDoorOffsetClamp(float RW);
	void DownDoorOffsetClamp(float RW);
	UChildActorComponent* SpawnRightDoor(int m, FVector loc, FRotator rot, UObject* Outer) const;
	UChildActorComponent* SpawnLeftDoor(int m, FVector loc, FRotator rot, UObject* Outer) const;
	UChildActorComponent* SpawnTopDoor(int n, FVector loc, FRotator rot, UObject* Outer) const;
	UChildActorComponent* SpawnDownDoor(int n, FVector loc, FRotator rot, UObject* Outer) const;
	void CenterRoom();
	void MoveRoomLeft();
	void MoveRoomRight();
	void MoveRoomUp();
	void MoveRoomDown();

	void ChangeCamera();

	void ComponentFollow(const AMainCharacter* Player);
	void CameraFollow(const AMainCharacter* Player);

	void SetCorners();

	void DeleteRoom();
	

};
