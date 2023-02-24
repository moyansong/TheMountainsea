// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SimpleCombatTypes.h"
#include "TheMountainseaTypes.generated.h"

class AActor;
class AMyCharacter;

UENUM(BlueprintType)
enum class ERelativeLocation : uint8
{
	ERL_Front	UMETA(DisplayName = "Front"),
	ERL_Back	UMETA(DisplayName = "Back"),
	ERL_Left	UMETA(DisplayName = "Left"),
	ERL_Right	UMETA(DisplayName = "Right"),
	ERL_Max		UMETA(DisplayName = "DefaultMax")
};


USTRUCT(BlueprintType)
struct THEMOUNTAINSEA_API FHitData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY()
	FHitResult HitResult;

	UPROPERTY()
	FGameplayEventData EventData;

	UPROPERTY()
	EHitType HitType;

	UPROPERTY()
	TWeakObjectPtr<AActor> HitCauser;

	UPROPERTY()
	TWeakObjectPtr<AMyCharacter> InstigatorCharacter;
};
