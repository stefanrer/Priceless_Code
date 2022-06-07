// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorTile5.generated.h"



UCLASS()
class PRICELESS_API AFloorTile5 : public AActor
{
	GENERATED_BODY()

	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UPaperSpriteComponent* SpriteComponent;

public:	
	// Sets default values for this actor's properties
	AFloorTile5();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// virtual void OnConstruction(const FTransform& Transform) override;
};

