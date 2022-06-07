// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "BaseStaticObject.generated.h"


UCLASS()
class PRICELESS_API ABaseStaticObject : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	UPROPERTY(Category = LightBlocker, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LightBlocker;
	
public:	
	// Sets default values for this actor's properties
	ABaseStaticObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
