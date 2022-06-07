// Copyright Epic Games, Inc. All Rights Reserved.

#include "PricelessGameModeBase.h"
#include "PricelessPlayerController.h"


APricelessGameModeBase::APricelessGameModeBase()
{
	DefaultPawnClass = nullptr;
	SpectatorClass = nullptr;
	PlayerControllerClass = APricelessPlayerController::StaticClass();
	
}
