// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PricelessCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PRICELESS_API APricelessCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	virtual void DoUpdateCamera(float DeltaTime) override;
};
