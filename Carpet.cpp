// Fill out your copyright notice in the Description page of Project Settings.


#include "Carpet.h"
#include "PaperSprite.h"

// Sets default values
ACarpet::ACarpet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/CARPET_Sprite.CARPET_Sprite'")));
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(SpriteComponent);
	RootComponent->SetMobility(EComponentMobility::Static);
	SpriteComponent->SetSprite(Sprite);
}

