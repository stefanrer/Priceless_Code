// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable_Storage1.h"
#include "PaperSprite.h"
#include "Priceless/Core/MainCharacter.h"
#include "Priceless/Game/PricelessGameInstance.h"

AInteractable_Storage1::AInteractable_Storage1()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	Root->SetMobility(EComponentMobility::Static);
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMesh")); //Добавить компонент
	SpriteComponent->SetupAttachment(RootComponent);
	SpriteComponent->SetGenerateOverlapEvents(false);
	SpriteComponent->CanCharacterStepUpOn = ECB_No;
	SpriteComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteComponent->SetMobility(EComponentMobility::Static);

	SpriteComponent2 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteMeshActive"));
	SpriteComponent2->SetupAttachment(RootComponent);
	SpriteComponent2->SetGenerateOverlapEvents(false);
	SpriteComponent2->CanCharacterStepUpOn = ECB_No;
	SpriteComponent2->SetCollisionResponseToAllChannels(ECR_Ignore);
	SpriteComponent2->SetMobility(EComponentMobility::Static);
	SpriteComponent2->SetVisibility(false);
	SpriteComponent2->SetHiddenInGame(true);
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision->SetGenerateOverlapEvents(false);
	BoxCollision->SetMobility(EComponentMobility::Static);

	BoxCollision2 = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision2"));
	BoxCollision2->SetupAttachment(RootComponent);
	BoxCollision2->SetBoxExtent({16.0f,32.0f,15.75f});
	BoxCollision2->SetRelativeLocation({0.0f, 0.0f, 3.0f});
	BoxCollision2->SetRelativeScale3D({1.8f, 1.0f, 1.8f});
	BoxCollision2->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxCollision2->SetGenerateOverlapEvents(true);
	BoxCollision2->SetMobility(EComponentMobility::Static);
	BoxCollision2->OnComponentBeginOverlap.AddDynamic( this, &AInteractable_Storage1::OnOverlapBegin );
	BoxCollision2->OnComponentEndOverlap.AddDynamic( this, &AInteractable_Storage1::OnOverlapEnd );
	

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
	
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Interactable/Seif1/seyf_1_Sprite.seyf_1_Sprite'")));
	SpriteComponent->SetSprite(Sprite);
	
	UPaperSprite* Sprite_active = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Interactable/Seif1/seyf_1_active_Sprite.seyf_1_active_Sprite'")));
	SpriteComponent2->SetSprite(Sprite_active);

	BoxCollision->SetBoxExtent({16.0f,32.0f,15.75f});
	BoxCollision->SetRelativeLocation({0.0f, 0.0f, 3.0f});
	
	LightBlocker->SetRelativeScale3D({0.320000f,1.000000f,0.320000f});


}

void AInteractable_Storage1::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractable_Storage1::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor)->bFlashLightOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped with character")); //For Debug
		SpriteComponent2->SetHiddenInGame(false);
		SpriteComponent2->SetVisibility(true);
		SpriteComponent->SetHiddenInGame(true);
		SpriteComponent->SetVisibility(false);
	}
}

void AInteractable_Storage1::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
	UE_LOG(LogTemp, Warning, TEXT("Overlapped with character")); //For Debug
	SpriteComponent2->SetHiddenInGame(true);
	SpriteComponent2->SetVisibility(false);
	SpriteComponent->SetHiddenInGame(false);
	SpriteComponent->SetVisibility(true);
}

void AInteractable_Storage1::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AInteractable_Storage1::OnInteract_Implementation(AActor* Caller)
{
	Super::OnInteract_Implementation(Caller);
	if (Cast<AMainCharacter>(Caller)->bFlashLightOn)
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact with storage"));
		if (!bEmpty)
		{
			Cast<UPricelessGameInstance>(GetGameInstance())->CreateStorageWidget();
		}
		else
		{
			Cast<UPricelessGameInstance>(GetGameInstance())->CreateEmptyStorageWidget();
		}
	}
}
