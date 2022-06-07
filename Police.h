// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "Components/SpotLightComponent.h"
#include "Police.generated.h"

UCLASS()
class PRICELESS_API APolice : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = "SpriteMesh", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;
	UPROPERTY(Category = "FlipBook", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperFlipbook* MoveFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, TEXT("PaperFlipbook'/Game/GameAssets/Police/POLICE_Walk.POLICE_Walk'")));
	UPROPERTY(Category = "FlipBook", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperFlipbook* IdleFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, TEXT("PaperFlipbook'/Game/GameAssets/Police/POLICE_Idle.POLICE_Idle'")));
	UPROPERTY(Category = FlashLight, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpotLightComponent* FlashLight;
	// Patrol AI Params
	UPROPERTY(Category = "Patrol AI", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess = "true"))
	bool bPatrol = true;
	// Patrol AI Params
	UPROPERTY(Category = "Patrol AI", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess = "true", ClampMax = 12, ClampMin = 0))
	float Box_Width = 12.f;
	
	UPROPERTY()
	bool bDoOnceIdle = true;
	UPROPERTY()
	bool bDoOnceMove = true;

	// Patrol AI Spatial Awareness
	UPROPERTY(Category = "Patrol AI|Spatial Awareness", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bLeftWall = false;
	// Patrol AI Spatial Awareness
	UPROPERTY(Category = "Patrol AI|Spatial Awareness", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bRightWall = false;
	// Patrol AI Spatial Awareness
	UPROPERTY(Category = "Patrol AI|Spatial Awareness", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bUPWall = false;
	// Patrol AI Spatial Awareness
	UPROPERTY(Category = "Patrol AI|Spatial Awareness", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	bool bDownWall = false;
	
	// Patrol AI Params
	UPROPERTY(Category = "Patrol AI", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess = "true"))
	bool bPatrolClock = false;
	// Patrol AI Params
	UPROPERTY(Category = "Patrol AI", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess = "true"))
	float FPatrolSpeed = 25.0f;

	// Patrol AI Params
	UPROPERTY(Category = "Patrol AI|TraceLine|Params", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess = "true", ClampMin = 20))
	float TraceDistance = 40;
	// Patrol AI Params
	UPROPERTY(Category = "Patrol AI|TraceLine|Params", EditAnywhere, BlueprintReadOnly,
		meta=(AllowPrivateAccess = "true"))
	float LifeTime = 0.05f;
	
public:	
	// Sets default values for this actor's properties
	APolice();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	//Patrol AI Function
	auto CheckLeftObstacle() const -> bool;
	//Patrol AI Function
	auto CheckRightObstacle() const -> bool;
	//Patrol AI Function
	auto CheckUpObstacle() const -> bool;
	//Patrol AI Function
	auto CheckDownObstacle() const -> bool;

	//Patrol AI Function
	void PatrolMoveSwitch(int State, float DeltaTime);
	//Patrol AI Function
	void Patrol(float DeltaTime, bool bMovementDirection);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};





