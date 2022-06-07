// Fill out your copyright notice in the Description page of Project Settings.


#include "LeftUpperAndRightLowerCorner.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

// Sets default values
ALeftUpperAndRightLowerCorner::ALeftUpperAndRightLowerCorner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Walls/Corners/LeftUpperCorner_Texture_Sprite.LeftUpperCorner_Texture_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	BoxCollision->SetBoxExtent({5.5,32,16});
	BoxCollision->SetRelativeLocation({-10.5, 0, 0});
	// BoxCollision1->SetHiddenInGame(false);

	BoxCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision2"));
	BoxCollision2->SetupAttachment(RootComponent);
	BoxCollision2->SetBoxExtent({5.5,32,16});
	BoxCollision2->SetRelativeLocation({0, 0, 10.5});
	BoxCollision2->SetRelativeRotation({90, 0, 0});
	// BoxCollision2->SetHiddenInGame(false);
	BoxCollision2->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision2->SetGenerateOverlapEvents(false);
	BoxCollision2->SetMobility(EComponentMobility::Static);


	LightBlocker->SetRelativeScale3D({0.11f, 0.65f, 0.32f});
	// LightBlocker->SetHiddenInGame(false); // For Debug
	// LightBlocker->SetVisibility(true); // For Debug

	LightBlocker2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightBlocker2"));
	LightBlocker2->SetVisibility(false); // Set Invinsible
	LightBlocker2->SetHiddenInGame(true); // Set Hidden in game
	LightBlocker2->SetupAttachment(BoxCollision2);
	LightBlocker2->SetCollisionResponseToAllChannels(ECR_Ignore);
	LightBlocker2->SetGenerateOverlapEvents(false);
	LightBlocker2->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	LightBlocker2->SetMobility(EComponentMobility::Static); // Set Mobility to Static
	LightBlocker2->SetRelativeScale3D({0.11f, 0.65f, 0.32f}); // Set Scale
	LightBlocker2->SetCastHiddenShadow(true); // Cast shadow while hidden in mame
	LightBlocker2->bCastStaticShadow = false; // Don't cast Static Shadows
	// LightBlocker2->SetVisibility(true);
	// LightBlocker2->SetHiddenInGame(false);

}

// Called when the game starts or when spawned
void ALeftUpperAndRightLowerCorner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALeftUpperAndRightLowerCorner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

