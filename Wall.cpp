// Fill out your copyright notice in the Description page of Project Settings.


#include "Wall.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Walls/HorWall_Sprite.HorWall_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({5.5,32,16});
	BoxCollision->SetRelativeLocation({-10.5f, 0.f, 0.f});
	// BoxCollision->SetHiddenInGame(false);

	LightBlocker->SetRelativeScale3D({0.11f, 0.65f, 0.32f});
	// LightBlocker->SetHiddenInGame(false); // For Debug
	// LightBlocker->SetVisibility(true); // For Debug

}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

