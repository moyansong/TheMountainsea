// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"

void UMyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	if (MyCharacter)
	{
		MyMovementComponent = MyCharacter->GetCharacterMovement();
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!MyCharacter)
	{
		MyCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
		if (!MyCharacter) return;
	}
	if (!MyMovementComponent)
	{
		MyMovementComponent = MyCharacter->GetCharacterMovement();
		if (!MyMovementComponent) return;
	}

	bIsAlive = MyCharacter->IsAlive();
	bIsCrouched = MyCharacter->bIsCrouched;
	bIsInAir = MyCharacter->GetCharacterMovement()->IsFalling();
	bIsAccelerating = MyCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0 ? true : false;

	Speed = UKismetMathLibrary::VSizeXY(MyMovementComponent->Velocity);

	FRotator AimRotation = MyCharacter->GetBaseAimRotation();
	FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(MyCharacter->GetVelocity());
	Direction = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

	if (bIsAlive) DeathPoseIndex = FMath::RandRange(0, DeathPoseNum);

	CharacterState = MyCharacter->GetCharacterState();
	CharacterMotionState = MyCharacter->GetCharacterMotionState();

	AimOffset(DeltaTime);
}

void UMyAnimInstance::AimOffset(float DeltaTime)
{
	if (MyCharacter && bIsAlive)
	{
		FRotator AimRotation = UKismetMathLibrary::NormalizedDeltaRotator(MyCharacter->GetBaseAimRotation(), MyCharacter->GetActorRotation());
		AO_Yaw = AimRotation.Yaw;
		AO_Pitch = AimRotation.Pitch;
	}
	else
	{
		AO_Yaw = 0.f;
		AO_Pitch = 0.f;
	}
}
