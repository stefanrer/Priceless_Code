// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Priceless/Interact/InteractableBase.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Interactable_Storage1.generated.h"

/**
 * 
 */
UCLASS()
class PRICELESS_API AInteractable_Storage1 : public AInteractableBase
{
	GENERATED_BODY()
	
	UPROPERTY(Category = SpriteComponent, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(Category = SpriteComponent, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent2;
	
	UPROPERTY(Category = LightBlocker, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LightBlocker;
	
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;
	
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision2;
	
	UPROPERTY(Category = RootComponent, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* Root;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEmpty = false;

	
public:
	AInteractable_Storage1();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
public:
	virtual void Tick(float DeltaSeconds) override;
	
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller) override;
	
};
