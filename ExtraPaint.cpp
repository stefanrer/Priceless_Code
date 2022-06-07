// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraPaint.h"

AExtraPaint::AExtraPaint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/ETRA_PAINT_Sprite.ETRA_PAINT_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({14.0f,32.0f,2.5f});
	BoxCollision->SetRelativeLocation({0.0f, 0.0f, 0.5f});
}


