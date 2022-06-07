// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "BaseStaticObject.h"
#include "LeftUpperAndRightLowerCorner.generated.h"

UCLASS()
class PRICELESS_API ALeftUpperAndRightLowerCorner : public ABaseStaticObject
{
	GENERATED_BODY()
	
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision2;
	
	UPROPERTY(Category = LightBlocker, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LightBlocker2;
	
public:	
	// Sets default values for this actor's properties
	ALeftUpperAndRightLowerCorner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
