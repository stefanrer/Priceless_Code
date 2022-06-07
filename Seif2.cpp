// Fill out your copyright notice in the Description page of Project Settings.


#include "Seif2.h"

ASeif2::ASeif2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/seyf_2_Sprite.seyf_2_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({16.0f,32.0f,10.0f});
	BoxCollision->SetRelativeLocation({0.0f, 0.0f, 2.0f});
}

