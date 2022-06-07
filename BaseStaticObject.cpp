// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseStaticObject.h"

// Sets default values
ABaseStaticObject::ABaseStaticObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(SpriteComponent);
	RootComponent->SetMobility(EComponentMobility::Static);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision->SetGenerateOverlapEvents(false);
	BoxCollision->SetMobility(EComponentMobility::Static);

	LightBlocker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LightBlocker"));
	LightBlocker->SetupAttachment(BoxCollision);
	LightBlocker->SetCollisionResponseToAllChannels(ECR_Ignore);
	LightBlocker->SetGenerateOverlapEvents(false);
	LightBlocker->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object);
	LightBlocker->SetMobility(EComponentMobility::Static); // Set Mobility to Static
	LightBlocker->SetRelativeScale3D({0.f, 0.f, 0.f}); // Set Scale
	LightBlocker->SetCastHiddenShadow(true); // Cast shadow while hidden in mame
	LightBlocker->bCastStaticShadow = false; // Don't cast Static Shadows
	LightBlocker->SetVisibility(false); // Set Invinsible
	LightBlocker->SetHiddenInGame(true); // Set Hidden in game
}

// Called when the game starts or when spawned
void ABaseStaticObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseStaticObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

