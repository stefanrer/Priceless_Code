// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "Flower.generated.h"

/**
 * 
 */
UCLASS()
class PRICELESS_API AFlower : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;

	AFlower();
};
