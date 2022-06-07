// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Priceless/StaticObjects/BaseStaticObject.h"
#include "Obstacle.generated.h"


UENUM()
enum EColumnType
{
	Column1 UMETA(DisplayName = "Column1"),
	Column2 UMETA(DisplayName = "Column2"),
	Column3 UMETA(DisplayName = "Column3")
  };
/**
 * 
 */
UCLASS()
class PRICELESS_API AObstacle : public ABaseStaticObject
{
	GENERATED_BODY()

	AObstacle();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="ColumnType")
	TEnumAsByte<EColumnType> ColumnTypeSelection = EColumnType::Column1;

	virtual void OnConstruction(const FTransform& Transform) override;
	
};

