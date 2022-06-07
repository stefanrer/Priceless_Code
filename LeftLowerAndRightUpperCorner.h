// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseStaticObject.h"
#include "Components/BoxComponent.h"
#include "LeftLowerAndRightUpperCorner.generated.h"

UCLASS()
class PRICELESS_API ALeftLowerAndRightUpperCorner : public ABaseStaticObject
{
	GENERATED_BODY()
	
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision2;

	UPROPERTY(Category = LightBlocker, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LightBlocker2;
	
public:	
	// Sets default values for this actor's properties
	ALeftLowerAndRightUpperCorner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
