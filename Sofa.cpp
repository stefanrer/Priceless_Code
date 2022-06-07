// Fill out your copyright notice in the Description page of Project Settings.


#include "Sofa.h"

ASofa::ASofa()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/Sofa_Texture_Sprite.Sofa_Texture_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({38.0f,32.0f,12.5f});
	BoxCollision->SetRelativeLocation({0.0f, 0.0f, 0.5f});

	LightBlocker->SetRelativeScale3D({0.750000,1.000000,0.250000});
}

