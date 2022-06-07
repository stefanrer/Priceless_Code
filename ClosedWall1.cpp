// Fill out your copyright notice in the Description page of Project Settings.


#include "ClosedWall1.h"
#include "PaperSprite.h"

// Sets default values
AClosedWall1::AClosedWall1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Walls/Closed_Wall1_Sprite.Closed_Wall1_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({5.5,32,16});
	BoxCollision->SetRelativeLocation({10.5, 0, 0});
	
	LightBlocker->SetRelativeScale3D({0.11f, 0.65f, 0.32f});
	// LightBlocker->SetHiddenInGame(false); // For Debug
	// LightBlocker->SetVisibility(true); // For Debug
}

