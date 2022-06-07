// Fill out your copyright notice in the Description page of Project Settings.


#include "PricelessPlayerController.h"
#include "Camera/PlayerCameraManager.h"

APricelessPlayerController::APricelessPlayerController()
{
	PlayerCameraManagerClass = APricelessCameraManager::StaticClass();
	DefaultMouseCursor = EMouseCursor::Default;
}
