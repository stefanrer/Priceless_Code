// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

AObstacle::AObstacle()
{
	UPaperSprite* Sprite1 = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/kolonna_1_Sprite.kolonna_1_Sprite'")));
	SpriteComponent->SetSprite(Sprite1);

	BoxCollision->SetRelativeScale3D({0.5f, 1.0f, 0.5f});

	LightBlocker->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'")).Object);
	LightBlocker->SetRelativeScale3D({0.625f, 0.3125f, 1.0f});
	LightBlocker->SetRelativeRotation({0.0f, 0.0f , 90.0f});
}

void AObstacle::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	switch (ColumnTypeSelection)
	{
	case (EColumnType::Column1):
		SpriteComponent->SetSprite(Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/kolonna_1_Sprite.kolonna_1_Sprite'"))));
		break;
	case (EColumnType::Column2):
		SpriteComponent->SetSprite(Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/kolonna_2_Sprite.kolonna_2_Sprite'"))));
		break;
	case (EColumnType::Column3):
		SpriteComponent->SetSprite(Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/kolonna_3_Sprite.kolonna_3_Sprite'"))));
		break;
	default:
		SpriteComponent->SetSprite(Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Decor/kolonna_1_Sprite.kolonna_1_Sprite'"))));
		break;
	}
}
