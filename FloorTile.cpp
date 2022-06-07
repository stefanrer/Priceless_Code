// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite1 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Floor/Floor_Texture_Sprite.Floor_Texture_Sprite'")));
	UPaperSprite* Sprite2 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Floor/Floor_Texture2_Sprite.Floor_Texture2_Sprite'")));
	UPaperSprite* Sprite3 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Floor/Floor_Texture3_Sprite.Floor_Texture3_Sprite'")));
	UPaperSprite* Sprite4 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Floor/Floor_Texture4_Sprite.Floor_Texture4_Sprite'")));
	UPaperSprite* Sprite5 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Floor/Floor_Texture5_Sprite.Floor_Texture5_Sprite'")));

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SetRootComponent(SpriteComponent);
	RootComponent->SetMobility(EComponentMobility::Static);
	// SpriteComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->SetSprite(Sprite1);
}

// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

