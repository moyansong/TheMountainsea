// Fill out your copyright notice in the Description page of Project Settings.


#include "MotionComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "../Characters/PlayerCharacters/PlayerCharacter.h"

UMotionComponent::UMotionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMotionComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UMotionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CharacterMotionState == ECharacterMotionState::ECMS_Flying)
	{
		Flying(DeltaTime);
	}
}

void UMotionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UMotionComponent, CharacterMotionState, COND_SimulatedOnly);
}

void UMotionComponent::SetCharacterMotionState(ECharacterMotionState State)
{
	if (CharacterMotionState == State) return;

	LastCharacterMotionState = CharacterMotionState;
	CharacterMotionState = State;
	OnCharacterMotionStateSet();
	if (MyCharacter.IsValid() && !MyCharacter->HasAuthority())
	{
		ServerSetCharacterMotionState(State);
	}
}

void UMotionComponent::ServerSetCharacterMotionState_Implementation(ECharacterMotionState State)
{
	SetCharacterMotionState(State);
}

void UMotionComponent::OnRep_CharacterMotionState(ECharacterMotionState OldState)
{
	LastCharacterMotionState = OldState;
	OnCharacterMotionStateSet();
}

void UMotionComponent::OnCharacterMotionStateSet()
{
	switch (CharacterMotionState)
	{
	case ECharacterMotionState::ECMS_Normal:
		HandleNormalStart();
		break;
	case ECharacterMotionState::ECMS_Flying:
		HandleFlyStart();
		break;
	case ECharacterMotionState::ECMS_Climbing:
		break;
	case ECharacterMotionState::ECMS_Swiming:
		break;
	case ECharacterMotionState::ECMS_Riding:
		break;
	default:
		break;
	}
}

void UMotionComponent::HandleNormalStart()
{
	if (!MyCharacter.IsValid() || !MyMovementComponent.IsValid() || !MyCapsuleComponent.IsValid()) return;

	if (LastCharacterMotionState == ECharacterMotionState::ECMS_Flying)
	{
		HandleFlyStop();
	}
}

void UMotionComponent::Fly()
{
	if (!MyCharacter.IsValid() || !MyMovementComponent.IsValid()) return;

	if (CharacterMotionState == ECharacterMotionState::ECMS_Normal)
	{
		if (MyMovementComponent->IsFalling())
		{
			FlyStart();
		}
		else
		{
			MyCharacter->Jump();
			MyCharacter->GetWorldTimerManager().SetTimer(
				FlyTimer,
				this,
				&UMotionComponent::FlyStart,
				0.7f,
				false
			);
		}
	}
	else if (CharacterMotionState == ECharacterMotionState::ECMS_Flying)
	{
		FlyStop();
	}
}

void UMotionComponent::FlyStart()
{
	if (CharacterMotionState == ECharacterMotionState::ECMS_Normal)
	{
		SetCharacterMotionState(ECharacterMotionState::ECMS_Flying);
	}
}

void UMotionComponent::FlyStop()
{
	if (CharacterMotionState == ECharacterMotionState::ECMS_Flying)
	{
		SetCharacterMotionState(ECharacterMotionState::ECMS_Normal);
	}
}

void UMotionComponent::HandleFlyStart()
{
	if (!MyCharacter.IsValid() || !MyMovementComponent.IsValid()) return;

	MyMovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
}

void UMotionComponent::HandleFlyStop()
{
	if (!MyCharacter.IsValid() || !MyMovementComponent.IsValid()) return;

	MyMovementComponent->SetMovementMode(EMovementMode::MOVE_Falling);
	FRotator CapsuleRotation = MyCapsuleComponent->GetComponentRotation();
	MyCharacter->SetActorRotation(FRotator(0.f, CapsuleRotation.Yaw, CapsuleRotation.Roll));
}

void UMotionComponent::FlyForward(float Value)
{
	if (MyCharacter.IsValid() && MyFollowCamera.IsValid())
	{
		MyCharacter->AddMovementInput(MyFollowCamera->GetForwardVector(), Value);
	}
}

void UMotionComponent::Flying(float DeltaTime)
{
	if (MyCharacter.IsValid() && MyMovementComponent.IsValid() && MyCapsuleComponent.IsValid() && MyFollowCamera.IsValid()
		&& (MyCharacter->GetLocalRole() == ENetRole::ROLE_Authority || MyCharacter->GetLocalRole() == ENetRole::ROLE_AutonomousProxy))
	{
		// 调整人物的旋转和速度，鼠标向上拉升时向上飞
		const FRotator CameraRotation = MyFollowCamera->GetComponentRotation();
		const FRotator CapsuleRotation = MyCapsuleComponent->GetComponentRotation();

		double TargetPitch = 0.f;
		if (MyPlayerCharacter.IsValid() && (MyPlayerCharacter->bWButtonPressed || MyPlayerCharacter->bSButtonPressed))
		{
			TargetPitch = CameraRotation.Pitch;
		}

		FRotator NewCapsuleRotation = MyCharacter->GetActorRotation();
		NewCapsuleRotation.Pitch = FMath::FInterpTo(CapsuleRotation.Pitch, TargetPitch, DeltaTime, 5.f);
		MyCharacter->SetActorRotation(NewCapsuleRotation);

		/*const FVector Velocity = MyMovementComponent->Velocity;
		const FVector NewVelocity = CapsuleRotation.Vector() * Velocity.Size();
		MyMovementComponent->Velocity = FMath::VInterpTo(Velocity, NewVelocity, DeltaTime, 5.f);*/
	}
}

