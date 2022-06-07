// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorTile2.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
AFloorTile2::AFloorTile2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite2 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Floor/Floor_Texture2_Sprite.Floor_Texture2_Sprite'")));
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SetRootComponent(SpriteComponent);
	RootComponent->SetMobility(EComponentMobility::Static);
	// SpriteComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->SetSprite(Sprite2);

	
	
}

// Called when the game starts or when spawned
void AFloorTile2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorTile2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


