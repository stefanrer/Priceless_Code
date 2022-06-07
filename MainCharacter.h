// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "PaperFlipbookComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PaperFlipbook.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SpotLightComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class PRICELESS_API AMainCharacter : public APawn
{
	GENERATED_BODY()

	UPROPERTY(Category = SpriteMesh, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* FlipbookComponent;
	UPROPERTY(Category = FlipBook, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UPaperFlipbook* MoveFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, TEXT("PaperFlipbook'/Game/GameAssets/Character/MainCharacterMove.MainCharacterMove'")));
	UPROPERTY(Category = FlipBook, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UPaperFlipbook* IdleFlipbook = Cast<UPaperFlipbook>(StaticLoadObject(UPaperFlipbook::StaticClass(), nullptr, TEXT("PaperFlipbook'/Game/GameAssets/Character/MainCharacterIdle.MainCharacterIdle'")));

	// UPROPERTY(Category = SpringArm, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	// USpringArmComponent* SpringArmComponent;
	//
	// UPROPERTY(Category = Camera, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	// UCameraComponent* CameraComponent;

	UPROPERTY(Category = PawnMovement, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UFloatingPawnMovement* PawnMovement;

	UPROPERTY(Category = CapsuleComponent, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UCapsuleComponent* CharacterCapsuleComponent;

	UPROPERTY(Category = SphereOverlap, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USphereComponent* SphereOverlap;

	UPROPERTY(Category = FlashLight, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpotLightComponent* FlashLight;

	UPROPERTY(Category = DeadChar, VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"))
	UPaperSpriteComponent* DeadChar;

public:	
	// Sets default values for this actor's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent * PlayerInputComponent) override;

	//Properties
	UPROPERTY(Category = CharacterMovement, VisibleAnywhere, BlueprintReadWrite, meta=(ClampMin="0"))
	float CharacterMaxSpeed = 70;
	UPROPERTY(Category = CharacterMovement, VisibleAnywhere, BlueprintReadWrite, meta=(ClampMin="0"))
	float CharacterAcceleration = 50;
	UPROPERTY(Category = CharacterMovement, VisibleAnywhere, BlueprintReadWrite, meta=(ClampMin="0"))
	float DeltaAcceletation = 70;
	UPROPERTY(Category = Interact, VisibleAnywhere, BlueprintReadOnly)
	bool bAbleToInteract = false;
	UPROPERTY(Category = FlashLight, VisibleAnywhere, BlueprintReadOnly)
	bool bFlashLightOn = true;
	UPROPERTY()
	AActor* FocusedActor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Widgetstate = 0;
	
	// Input functions
	void MoveForwardBack(float AxisValue);
	void MoveRightLeft(float AxisValue);

	

	// Rotation function
	// void RotateFlipBook(FVector velocity) const;

	// Anim State Machine
	void AnimStateMachine() const;

	//Interact
	void Interact();

	//OpenMenu
	void PauseMenu();
	
	//FlashLight
	void FlashLightTurnOnOff();
	//Menu
	void InventoryMenu();
};
