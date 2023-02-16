// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "../../Characters/CharacterTypes.h"
#include "MyAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EMoveDirection : uint8
{
	EMD_Idle UMETA(DisplayName = "Idle"),
	EMD_Forward UMETA(DisplayName = "Forward"),
	EMD_Backward UMETA(DisplayName = "Backward"),
	EMD_Right UMETA(DisplayName = "Right"),
	EMD_Left UMETA(DisplayName = "Left"),
	EWS_MAX UMETA(DisplayName = "DefaultMax") 
};

class AMyCharacter;
class APlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class THEMOUNTAINSEA_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	friend class AMyCharacter;

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	void AimOffset(float DeltaTime);

protected:
//------------------------------------------Parameters----------------------------------------------------------
	UPROPERTY(BlueprintReadWrite, Category = Paramters, meta = (AllowPrivateAccess = "true"))
	AMyCharacter* MyCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Paramters, meta = (AllowPrivateAccess = "true"))
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly, Category = Paramters, meta = (AllowPrivateAccess = "true"))
	ECharacterMotionState CharacterMotionState;

	UPROPERTY(BlueprintReadOnly, Category = Parameters, meta = (AllowPrivateAccess = "true"))
	int32 DeathPoseIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameters, meta = (AllowPrivateAccess = "true"))
	int32 DeathPoseNum = 5;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UCharacterMovementComponent* MyMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsInAir;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAccelerating;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsCrouched;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	bool bIsAlive = true;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Direction;

	// 由按键顺序决定，先按W则代表向前
	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	EMoveDirection DirectionType = EMoveDirection::EMD_Idle;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float AO_Yaw;

	UPROPERTY(BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float AO_Pitch;
};
