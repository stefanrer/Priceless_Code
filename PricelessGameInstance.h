// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Blueprint/UserWidget.h"
#include "PricelessGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PRICELESS_API UPricelessGameInstance : public UGameInstance
{
	GENERATED_BODY()

	UPricelessGameInstance(const FObjectInitializer& ObjectInitializer);
private:
	UPROPERTY()
	TSubclassOf<class UUserWidget> StorageWidgetClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> PaintingWidgetClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> HudWidgetClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> StorageEmptyWidgetClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> InventoryEmptyWidgetClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> InventoryPaintWidgetClass;
	UPROPERTY()
	TSubclassOf<class UUserWidget> InventoryFullWidgetClass;
public:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* StorageWidgetRef;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* StorageEmptyWidgetRef;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* PaintingWidgetRef;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HudWidgetRef;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* InventoryWidgetRef;
private:
	UPROPERTY()
	bool bStorageMenu = false;
	UPROPERTY()
	bool bEmptyStorageMenu = false;
	UPROPERTY()
	bool bPaintingMenu = false;
	UPROPERTY()
	bool bInv = false;
public:
	void CreateStorageWidget();
	void CreatePaintingWidget();
	void CreateHudWidget();
	void CreateEmptyStorageWidget();
	void CreateInventoryWidget(float state);
};
