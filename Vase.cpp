// Fill out your copyright notice in the Description page of Project Settings.


#include "Vase.h"

AVase::AVase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/Vase_Sprite.Vase_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({10.5f,32.0f,10.5f});
	BoxCollision->SetRelativeLocation({-0.5f, 0.0f, 0.5f});
}


