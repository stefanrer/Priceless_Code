// Fill out your copyright notice in the Description page of Project Settings.


#include "ClosedWall2.h"
#include "PaperSprite.h"

// Sets default values
AClosedWall2::AClosedWall2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Walls/Closed_Wall2_Sprite.Closed_Wall2_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	SpriteComponent->SetMobility(EComponentMobility::Static);
	
	BoxCollision->SetBoxExtent({5.5,32,16});
	BoxCollision->SetRelativeLocation({-10.5, 0, 0});
	// BoxCollision->SetHiddenInGame(false);
	
	LightBlocker->SetRelativeScale3D({0.11f, 0.65f, 0.32f});
	//LightBlocker->SetHiddenInGame(false); // For Debug
	// LightBlocker->SetVisibility(true); // For Debug

}

// Called when the game starts or when spawned
void AClosedWall2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AClosedWall2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

