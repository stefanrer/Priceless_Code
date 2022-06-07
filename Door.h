// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Priceless/Interact/InteractableBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "Door.generated.h"

UCLASS()
class PRICELESS_API ADoor : public AInteractableBase
{
	GENERATED_BODY()
	
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision1;
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision2;
	UPROPERTY(Category = SceneComponent, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	UPROPERTY(Category = TraceLine, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float TraceDistance = 100;
	UPROPERTY(Category = BoxCollision, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;
	UPROPERTY(Category = LightBlocker, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UStaticMeshComponent* LightBlocker;
	
	FTimerHandle DoorTimerHandle;
	UPROPERTY(Category = Timer, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	float MaxDelayTime = 1;

	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	FVector TeleportLoc;

private:
	UPROPERTY()
	bool DoorClosed = false;
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller) override;
	UFUNCTION()
	bool FindEndPointDoor();
	UFUNCTION()
	void TeleportCharacter(AActor* MainCharacter);

};
