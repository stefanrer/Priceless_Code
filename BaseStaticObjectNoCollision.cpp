// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStaticObjectNoCollision.h"

// Sets default values
ABaseStaticObjectNoCollision::ABaseStaticObjectNoCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/Paper_Texture_Sprite.Paper_Texture_Sprite'")));
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(SpriteComponent);
	RootComponent->SetMobility(EComponentMobility::Static);
}

// Called when the game starts or when spawned
void ABaseStaticObjectNoCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseStaticObjectNoCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

