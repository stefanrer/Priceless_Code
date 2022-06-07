// Fill out your copyright notice in the Description page of Project Settings.


#include "PricelessGameInstance.h"
#include "UObject/ConstructorHelpers.h"


UPricelessGameInstance::UPricelessGameInstance(const FObjectInitializer& ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> StorageWidget(TEXT("/Game/Widget/Storage/Storage1"));
	if (!ensure (StorageWidget.Class != nullptr)) return;
	StorageWidgetClass = StorageWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> PaintingWidget(TEXT("/Game/Widget/Painting/PaintingMenu"));
	if (!ensure (PaintingWidget.Class != nullptr)) return;
	PaintingWidgetClass = PaintingWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> HudWidget(TEXT("/Game/Widget/HUD"));
	if (!ensure (HudWidget.Class != nullptr)) return;
	HudWidgetClass = HudWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> EmptyStorageWidget(TEXT("/Game/Widget/Storage/StorageEmpty"));
	if (!ensure (EmptyStorageWidget.Class != nullptr)) return;
	StorageEmptyWidgetClass = EmptyStorageWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryWidgetEmpty(TEXT("/Game/Widget/Inv/InventoryEmpty"));
	if (!ensure (InventoryWidgetEmpty.Class != nullptr)) return;
	InventoryEmptyWidgetClass = InventoryWidgetEmpty.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryPaintWidget(TEXT("/Game/Widget/Inv/InventoryPaint"));
	if (!ensure (InventoryPaintWidget.Class != nullptr)) return;
	InventoryPaintWidgetClass = InventoryPaintWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryFullWidget(TEXT("/Game/Widget/Inv/InventoryFull"));
	if (!ensure (InventoryFullWidget.Class != nullptr)) return;
	InventoryFullWidgetClass = InventoryFullWidget.Class;
	
}

void UPricelessGameInstance::CreateStorageWidget()
{
	/* Create Widget and add it to viewport */
	if (!bStorageMenu)
	{
		UUserWidget* StorageMenu = CreateWidget(this, StorageWidgetClass, TEXT("StorageWidget"));
		StorageMenu->AddToViewport();
		StorageWidgetRef = StorageMenu;

		/* Get reference to Player Controller */
		APlayerController* PlayerController = GetFirstLocalPlayerController();

		/* Set Up input parameters to the SetInputMode function */
		FInputModeGameAndUI InputModeData;
		InputModeData.SetWidgetToFocus(StorageMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		/* Set Input Mode */
		PlayerController->SetInputMode(InputModeData);

		/* Show mouse cursor */
		PlayerController->bShowMouseCursor = true;
		bStorageMenu = true;
	}
	else
	{
		StorageWidgetRef->RemoveFromParent();
		StorageWidgetRef = nullptr;
		bStorageMenu = false;
		GetFirstLocalPlayerController()->bShowMouseCursor = false;
		GetFirstLocalPlayerController()->SetShowMouseCursor(false);
		FInputModeGameOnly InputModeData;
		GetFirstLocalPlayerController()->SetInputMode(InputModeData);
	}
}

void UPricelessGameInstance::CreatePaintingWidget()
{
	if (!bPaintingMenu)
	{
		UUserWidget* PaintingMenu = CreateWidget(this, PaintingWidgetClass, TEXT("PaintingWidget"));
		PaintingMenu->AddToViewport();
		PaintingWidgetRef = PaintingMenu;

		/* Get reference to Player Controller */
		APlayerController* PlayerController = GetFirstLocalPlayerController();

		/* Set Up input parameters to the SetInputMode function */
		FInputModeGameAndUI InputModeData;
		InputModeData.SetWidgetToFocus(PaintingMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		/* Set Input Mode */
		PlayerController->SetInputMode(InputModeData);

		/* Show mouse cursor */
		PlayerController->bShowMouseCursor = true;
		bPaintingMenu = true;
	}
	else
	{
		PaintingWidgetRef->RemoveFromParent();
		PaintingWidgetRef = nullptr;
		bPaintingMenu = false;
		GetFirstLocalPlayerController()->bShowMouseCursor = false;
		GetFirstLocalPlayerController()->SetShowMouseCursor(false);
		FInputModeGameOnly InputModeData;
		GetFirstLocalPlayerController()->SetInputMode(InputModeData);
	}
}

void UPricelessGameInstance::CreateHudWidget()
{
	UUserWidget* HudMenu = CreateWidget(this, HudWidgetClass, TEXT("HudWidget"));
	HudMenu->AddToViewport();
	HudWidgetRef = HudMenu;

	/* Get reference to Player Controller */
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	/* Set Up input parameters to the SetInputMode function */
	FInputModeGameOnly InputModeData;

	/* Set Input Mode */
	PlayerController->SetInputMode(InputModeData);

	/* Show mouse cursor */
	PlayerController->bShowMouseCursor = false;
	GetFirstLocalPlayerController()->SetShowMouseCursor(false);
	
}

void UPricelessGameInstance::CreateEmptyStorageWidget()
{
	/* Create Widget and add it to viewport */
	if (!bEmptyStorageMenu)
	{
		UUserWidget* StorageEmptyMenu = CreateWidget(this, StorageEmptyWidgetClass, TEXT("StorageEmptyWidget"));
		StorageEmptyMenu->AddToViewport();
		StorageEmptyWidgetRef = StorageEmptyMenu;

		/* Get reference to Player Controller */
		APlayerController* PlayerController = GetFirstLocalPlayerController();

		/* Set Up input parameters to the SetInputMode function */
		FInputModeGameAndUI InputModeData;
		InputModeData.SetWidgetToFocus(StorageEmptyMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		/* Set Input Mode */
		PlayerController->SetInputMode(InputModeData);

		/* Show mouse cursor */
		PlayerController->bShowMouseCursor = true;
		bEmptyStorageMenu = true;
	}
	else
	{
		StorageEmptyWidgetRef->RemoveFromParent();
		StorageEmptyWidgetRef = nullptr;
		bEmptyStorageMenu = false;
		GetFirstLocalPlayerController()->bShowMouseCursor = false;
		GetFirstLocalPlayerController()->SetShowMouseCursor(false);
		FInputModeGameOnly InputModeData;
		GetFirstLocalPlayerController()->SetInputMode(InputModeData);
	}
}

void UPricelessGameInstance::CreateInventoryWidget(float state)
{
	if (!bInv)
	{
		UUserWidget* InventoryWidgetMenu;
		if (state == 0) // Empty
		{
			InventoryWidgetMenu = CreateWidget(this, InventoryEmptyWidgetClass, TEXT("InventoryEmptyWidget"));

		}
		else if (state == 1) // Paint
		{
			InventoryWidgetMenu = CreateWidget(this, InventoryPaintWidgetClass, TEXT("InventoryPaintWidget"));

		}
		else if (state == 2) // Full
		{
			InventoryWidgetMenu = CreateWidget(this, InventoryFullWidgetClass, TEXT("InventoryFullWidget"));

		}
		else
		{
			InventoryWidgetMenu = CreateWidget(this, InventoryEmptyWidgetClass, TEXT("InventoryEmptyWidget"));
		}
		InventoryWidgetMenu->AddToViewport();
		InventoryWidgetRef = InventoryWidgetMenu;
		

		/* Get reference to Player Controller */
		APlayerController* PlayerController = GetWorld()->GetGameInstance()->GetFirstLocalPlayerController();

		/* Set Up input parameters to the SetInputMode function */
		FInputModeGameAndUI InputModeData;
		InputModeData.SetWidgetToFocus(InventoryWidgetMenu->TakeWidget());
		InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

		/* Set Input Mode */
		PlayerController->SetInputMode(InputModeData);

		/* Show mouse cursor */
		PlayerController->bShowMouseCursor = true;
		bInv = true;
	}
	else
	{
		InventoryWidgetRef->RemoveFromParent();
		InventoryWidgetRef = nullptr;
		bInv = false;
		GetFirstLocalPlayerController()->bShowMouseCursor = false;
		GetFirstLocalPlayerController()->SetShowMouseCursor(false);
		FInputModeGameOnly InputModeData;
		GetFirstLocalPlayerController()->SetInputMode(InputModeData);
	}
}
