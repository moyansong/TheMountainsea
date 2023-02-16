// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "../../Characters/PlayerCharacters/PlayerCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (MyCharacter)
	{
		MyPlayerCharacter = Cast<APlayerCharacter>(MyCharacter);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!MyPlayerCharacter)
	{
		MyPlayerCharacter = Cast<APlayerCharacter>(TryGetPawnOwner());
		if (!MyPlayerCharacter) return;
	}

	if (FMath::IsNearlyEqual(Speed, 0.f)) DirectionType = EMoveDirection::EMD_Idle;
	if (MyPlayerCharacter->bWButtonPressed && !MyPlayerCharacter->bSButtonPressed && !MyPlayerCharacter->bDButtonPressed && !MyPlayerCharacter->bAButtonPressed) DirectionType = EMoveDirection::EMD_Forward;
	if (MyPlayerCharacter->bSButtonPressed && !MyPlayerCharacter->bWButtonPressed && !MyPlayerCharacter->bDButtonPressed && !MyPlayerCharacter->bAButtonPressed) DirectionType = EMoveDirection::EMD_Backward;
	if (MyPlayerCharacter->bDButtonPressed && !MyPlayerCharacter->bSButtonPressed && !MyPlayerCharacter->bWButtonPressed && !MyPlayerCharacter->bAButtonPressed) DirectionType = EMoveDirection::EMD_Right;
	if (MyPlayerCharacter->bAButtonPressed && !MyPlayerCharacter->bSButtonPressed && !MyPlayerCharacter->bDButtonPressed && !MyPlayerCharacter->bWButtonPressed) DirectionType = EMoveDirection::EMD_Left;
}
