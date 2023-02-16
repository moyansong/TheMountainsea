// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SimpleCombatTypes.generated.h"

class UAnimMontage;

/**
* 长短按键
**/
USTRUCT(BlueprintType)
struct SIMPLECOMBAT_API FSimpleComboCheck
{
	GENERATED_USTRUCT_BODY()

	FSimpleComboCheck();

	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	int32 ComboIndex;

	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	bool bLongPressed;

	UPROPERTY(EditDefaultsOnly, Category = ComboAttack)
	bool bShortPressed;

	class ISimpleCombatInterface* Character;

	// Combo最大段数
	UPROPERTY()
	int32 MaxIndex;

	UPROPERTY()
	FName ComboName;

	void UpdateComboIndex();

	void Pressed();

	void Released();

	void Reset();

	FSimpleDelegate PressDelegate;
	FSimpleDelegate ReleasedDelegate;
	FSimpleDelegate ResetDelegate;
	FSimpleDelegate UpdateDelegate;
};

UENUM(BlueprintType)
enum class EAnimSignalType : uint8
{
	EAST_ComboReset UMETA(DisplayName = "ComboReset"),
	EAST_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EHitType : uint8
{
	EHT_None UMETA(DisplayName = "None"),			// 人物不产生任何受击反应
	EHT_SlightHit UMETA(DisplayName = "SlightHit"), // 轻微的受击，多为原地动作
	EHT_HeavyHit UMETA(DisplayName = "HeavyHit"),	// 重击，可产生位移
	EAST_MAX UMETA(DisplayName = "DefaultMAX")
};

