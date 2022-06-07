// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStaticObject.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Paper.generated.h"

/**
 * 
 */
UCLASS()
class PRICELESS_API APaper : public AActor
{
	GENERATED_BODY()
public:
	APaper();
	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;
	
};
