// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../../TheMountainsea.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Components/CombatComponent.h"
#include "../../Components/MotionComponent.h"
#include "../../Components/EquipmentComponent.h"
#include "../../Components/PlayerCombatComponent.h"
#include "../../Abilities/MyAbilitySystemComponent.h"
#include "../../Game/PlayerControllers/UIPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	TurnRateGamepad = 50.f;

	CharacterType = ECharacterType::ECT_Player;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 80.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("CombatComponent"));
	CombatComponent->SetIsReplicated(true);
	PlayerCombatComponent = Cast<UPlayerCombatComponent>(CombatComponent);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetCombatComponent())
	{
		GetCombatComponent()->MyPlayerCharacter = this;
	}
	if (GetMotionComponent())
	{
		GetMotionComponent()->MyPlayerCharacter = this;
		GetMotionComponent()->MyFollowCamera = FollowCamera;
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AUIPlayerController* PlayerController = Cast<AUIPlayerController>(NewController))
	{
		PlayerController->AcknowledgePossession(this);
		PossessedBy(PlayerController);
	}
}

void APlayerCharacter::PossessedBy(AUIPlayerController* NewController)
{
	MyController = NewController;
	if (MyController.IsValid())
	{
		if (GetCombatComponent())
		{
			GetCombatComponent()->MyPlayerController = MyController;
		}
		if (GetMotionComponent())
		{
			GetMotionComponent()->MyPlayerController = MyController;
		}
		if (GetEquipmentComponent())
		{
			GetEquipmentComponent()->MyPlayerController = MyController;
		}
	}
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetLocalRole() == ENetRole::ROLE_AutonomousProxy)
	{
		if (GetMyAbilitySystemComponent())
		{
			GetMyAbilitySystemComponent()->InitAbilityActorInfo(this, this);
			GetMyAbilitySystemComponent()->LocalInitAbility();
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	ACharacter::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpStart);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::JumpStop);
	PlayerInputComponent->BindAction("Fly", IE_Pressed, this, &APlayerCharacter::Fly);
	//PlayerInputComponent->BindAction("Fly", IE_Released, this, &APlayerCharacter::FlyStop);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &APlayerCharacter::Dodge);
	PlayerInputComponent->BindAction("MouseLeftClick", IE_Pressed, this, &APlayerCharacter::MouseLeftClickStart);
	PlayerInputComponent->BindAction("MouseLeftClick", IE_Released, this, &APlayerCharacter::MouseLeftClickStop);
	PlayerInputComponent->BindAction("MouseRightClick", IE_Pressed, this, &APlayerCharacter::MouseRightClickStart);
	PlayerInputComponent->BindAction("MouseRightClick", IE_Released, this, &APlayerCharacter::MouseRightClickStop);
	PlayerInputComponent->BindAction("Test", IE_Pressed, this, &APlayerCharacter::Test);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
}

void APlayerCharacter::Test()
{

}

void APlayerCharacter::MoveForward(float Value)
{
	if (bDisableGameplay) return;

	bWButtonPressed = FMath::IsNearlyEqual(Value, 1.f);
	bSButtonPressed = FMath::IsNearlyEqual(Value, -1.f);
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		if (GetCharacterMotionState() == ECharacterMotionState::ECMS_Flying && GetMotionComponent())
		{
			GetMotionComponent()->FlyForward(Value);
		}
		else
		{
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (bDisableGameplay) return;

	bDButtonPressed = FMath::IsNearlyEqual(Value, 1.f);
	bAButtonPressed = FMath::IsNearlyEqual(Value, -1.f);
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::JumpStart()
{
	if (bDisableGameplay) return;

	Jump();
}

void APlayerCharacter::JumpStop()
{
	if (bDisableGameplay) return;

	StopJumping();
}

void APlayerCharacter::Fly()
{
	if (bDisableGameplay) return;

	if (GetMotionComponent())
	{
		GetMotionComponent()->Fly();
	}
}

void APlayerCharacter::Dodge()
{
	if (bDisableGameplay) return;

	if (GetCombatComponent())
	{
		GetCombatComponent()->Dodge();
	}
}

void APlayerCharacter::Die()
{
	Super::Die();

	bDisableGameplay = true;
}

void APlayerCharacter::AnimSignal(EAnimSignalType AnimSignalType)
{
	Super::AnimSignal(AnimSignalType);

	if (AnimSignalType == EAnimSignalType::EAST_ComboReset)
	{
		if ((IsLocallyControlled() || HasAuthority()) && GetCombatComponent())
		{
			GetCombatComponent()->ComboReset(GetCombatComponent()->GetActiveSkill());
		}
	}
}

void APlayerCharacter::MouseLeftClickStart()
{
	if (bDisableGameplay) return;

	if (GetCombatComponent())
	{
		GetCombatComponent()->ComboPressed(TEXT("NormalAttack"));
	}
}

void APlayerCharacter::MouseLeftClickStop()
{
	if (bDisableGameplay) return;

	if (GetCombatComponent())
	{
		GetCombatComponent()->ComboReleased(TEXT("NormalAttack"));
	}
}

void APlayerCharacter::MouseRightClickStart()
{
	if (bDisableGameplay) return;

}

void APlayerCharacter::MouseRightClickStop()
{
	if (bDisableGameplay) return;

}

void APlayerCharacter::ComboShortPressed(const FName& ComboName)
{
	if (IsLocallyControlled())
	{
		ActivateSkill(ComboName);
	}
}

void APlayerCharacter::ComboLongPressed(const FName& ComboName)
{
	if (IsLocallyControlled())
	{
		FString ComboName_Heavy = ComboName.ToString().Append((TEXT("_Heavy")));
		ActivateSkill(FName(*ComboName_Heavy));
	}
}

