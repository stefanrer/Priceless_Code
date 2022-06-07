// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "Priceless/Interact/Door.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "PaperFlipbook.h"
#include "PaperSprite.h"
#include "Priceless/Game/PricelessGameInstance.h"
#include "Priceless/Interact/InteractInterface.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CharacterCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CharacterCapsuleComponent);
	CharacterCapsuleComponent->SetEnableGravity(false);
	// CharacterCapsuleComponent->SetCapsuleRadius(12.0f); //Normal Collision Radius
	// CharacterCapsuleComponent->SetCapsuleHalfHeight(17.0f); //Normal Collision Radius
	CharacterCapsuleComponent->SetCapsuleRadius(8.0f); //Вплотную к телу
	CharacterCapsuleComponent->SetCapsuleHalfHeight(8.0f); //Вплотную к телу
	CharacterCapsuleComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CharacterCapsuleComponent->SetConstraintMode(EDOFMode::XZPlane);
	CharacterCapsuleComponent->SetGenerateOverlapEvents(false);
	// CharacterCapsuleComponent->SetHiddenInGame(false); //For Debug

	DeadChar = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Dead Char"));
	UPaperSprite* Sprite = Cast<UPaperSprite>(StaticLoadObject(UPaperSprite::StaticClass(), nullptr, TEXT("PaperSprite'/Game/GameAssets/Character/DED_Sprite.DED_Sprite'")));
	DeadChar->SetSprite(Sprite);
	DeadChar->SetGenerateOverlapEvents(false);
	DeadChar->CanCharacterStepUpOn = ECB_No;
	DeadChar->SetCollisionResponseToAllChannels(ECR_Ignore);
	DeadChar->SetupAttachment(RootComponent);
	DeadChar->SetVisibility(false);
	DeadChar->SetRelativeScale3D({0.8f,0.8f,0.8f});

	SphereOverlap = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Overlap"));
	SphereOverlap->SetupAttachment(RootComponent);
	SphereOverlap->SetSphereRadius(40.0f);
	SphereOverlap->SetCollisionResponseToAllChannels(ECR_Overlap);
	SphereOverlap->SetRelativeScale3D({0.6f, 0.6f, 0.6f});
	SphereOverlap->SetEnableGravity(false);
	// SphereOverlap->SetHiddenInGame(false); //For Debug
	SphereOverlap->SetGenerateOverlapEvents(true);
	SphereOverlap->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnOverlapBegin);
	SphereOverlap->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnOverlapEnd);
	
	
	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Flipbook"));
	FlipbookComponent->SetFlipbook(IdleFlipbook);
	FlipbookComponent->SetupAttachment(CharacterCapsuleComponent);
	FlipbookComponent->SetEnableGravity(false);
	
	// SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	// SpringArmComponent->SetupAttachment(FlipbookComponent);
	// SpringArmComponent->SetRelativeRotation(FVector(0.0f, -90.0f, 0.0f).Rotation());
	// SpringArmComponent->SetAbsolute(false, false, false);
	// SpringArmComponent->TargetArmLength = 500.f;
	// SpringArmComponent->bDoCollisionTest = false;
	// SpringArmComponent->bInheritPitch = false;
	// SpringArmComponent->bInheritYaw = false;
	// SpringArmComponent->bInheritRoll = false;
	//
	// CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	// CameraComponent->SetupAttachment(SpringArmComponent);
	// CameraComponent->ProjectionMode = ECameraProjectionMode::Perspective;
	// CameraComponent->FieldOfView = 30.0f; // Camera Height // Old Perspective Camera
	
	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Flash Light"));
	FlashLight->SetupAttachment(FlipbookComponent);
	FlashLight->SetRelativeLocation({5.0f,0.0f,5.0f});
	FlashLight->SetRelativeRotation({90.0f, 0.0f,0.0f});
	FlashLight->Intensity = 600.0f;
	FlashLight->LightColor = FColor::FromHex("6DFFDAFF");
	FlashLight->AttenuationRadius = 172.0f;
	FlashLight->InnerConeAngle = 20.0f;
	FlashLight->OuterConeAngle = 30.0f;

	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	PawnMovement->MaxSpeed = CharacterMaxSpeed;
	PawnMovement->Acceleration = CharacterAcceleration;
	PawnMovement->TurningBoost = 20.0f;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<UPricelessGameInstance>(GetGameInstance())->CreateHudWidget();
}

void AMainCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s Overlap"), *OtherActor->GetActorLabel()));
	bAbleToInteract = true;
	if (FocusedActor != OtherActor)
	{
		FocusedActor = OtherActor;
	}
}

void AMainCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("%s EndOverlap"), *OtherActor->GetActorLabel()));
	bAbleToInteract = false;
	FocusedActor = nullptr;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	{
		AnimStateMachine();
		// UE_LOG(LogTemp, Warning, TEXT("X = %f"), GetActorLocation().X);
	}
}

void AMainCharacter::MoveForwardBack(float AxisValue)
{
	// UE_LOG(LogTemp, Warning, TEXT("Move Forward axis: %f"), AxisValue); //For Debug

	AddMovementInput(GetActorUpVector(), (GetWorld()->GetDeltaSeconds() * AxisValue * DeltaAcceletation));
	if (AxisValue == 1.0f)
	{
		FlipbookComponent->SetRelativeRotation({0, GetActorRotation().Yaw, GetActorRotation().Roll});
	}
	else if (AxisValue == -1.0f)
	{
		FlipbookComponent->SetRelativeRotation({180.0f, GetActorRotation().Yaw, GetActorRotation().Roll});
	}
}

void AMainCharacter::MoveRightLeft(float AxisValue)
{
	// UE_LOG(LogTemp, Warning, TEXT("Move Right axis: %f"), AxisValue); //For Debug

	AddMovementInput(GetActorForwardVector(), (GetWorld()->GetDeltaSeconds() * AxisValue * DeltaAcceletation));
	if (AxisValue == 1.0f)
	{
		FlipbookComponent->SetRelativeRotation({-90.0f, GetActorRotation().Yaw, GetActorRotation().Roll});
	}
	else if (AxisValue == -1.0f)
	{
		FlipbookComponent->SetRelativeRotation({90.0f, GetActorRotation().Yaw, GetActorRotation().Roll});
	}
}

void AMainCharacter::AnimStateMachine() const
{
	if (!GetVelocity().IsZero())
	{
		FlipbookComponent->SetFlipbook(MoveFlipbook);
		// RotateFlipBook(GetVelocity());
	}
	else
	{
		FlipbookComponent->SetFlipbook(IdleFlipbook);
	}
}

void AMainCharacter::Interact()
{
	// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Try Interact")));
	if (bAbleToInteract)
	{
		const IInteractInterface* Interface = Cast<IInteractInterface>(FocusedActor);
		if (Interface)
		{
			// GEngine->AddOnScreenDebugMessage(-1,200,FColor::Green,FString::Printf(TEXT("Interacted with %s"), *FocusedActor->GetActorLabel()));
			Interface->Execute_OnInteract(FocusedActor, this);
		}
	}
}

void AMainCharacter::PauseMenu()
{
	
}

void AMainCharacter::FlashLightTurnOnOff()
{
	if (bFlashLightOn)
	{
		bFlashLightOn = false;
		FlashLight->SetVisibility(false);
	}
	else
	{
		bFlashLightOn = true;
		FlashLight->SetVisibility(true);
	}
}

void AMainCharacter::InventoryMenu()
{
	Cast<UPricelessGameInstance>(GetGameInstance())->CreateInventoryWidget(Widgetstate);
}

/*
void AMainCharacter::RotateFlipBook(FVector velocity) const
{
	float Pitch = FlipbookComponent->GetRelativeRotation().Pitch;
	
	if (velocity.Z < 0)
	{
		Pitch = 180.0f;
	}
	if (velocity.Z > 0)
	{
		Pitch = 0.0f;
	}
	if (velocity.X > 0)
	{
		Pitch = -90.0f;
	}
	if (velocity.X < 0)
	{
		Pitch = 90.0f;
	}
	if (velocity.X < 0 && velocity.Z > 0)
	{
		Pitch = 45.0f;
	}
	if (velocity.X > 0 && velocity.Z > 0)
	{
		Pitch = -45.0f;
	}
	if (velocity.X < 0 && velocity.Z < 0)
	{
		Pitch = 135.0f;
	}
	if (velocity.X > 0 && velocity.Z < 0)
	{
		Pitch = -135.0f;
	}
	FlipbookComponent->SetRelativeRotation({Pitch, GetActorRotation().Yaw, GetActorRotation().Roll});
}
*/

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// Respond every frame to the values of our two movement axes, "MoveZ" and "MoveX".
	PlayerInputComponent->BindAxis("MoveUp", this, &AMainCharacter::MoveForwardBack);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRightLeft);
	
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::Interact);
	PlayerInputComponent->BindAction("PauseMenu", IE_Pressed, this, &AMainCharacter::PauseMenu);
	PlayerInputComponent->BindAction("FlashLight", IE_Pressed, this, &AMainCharacter::FlashLightTurnOnOff);
	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AMainCharacter::InventoryMenu);
	
	
}

