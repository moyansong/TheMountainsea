// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterSkillTable.generated.h"

class UGameplayAbility;

/**
 *
 */
USTRUCT(BlueprintType)
struct  FCharacterSkillTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterSkillTable();

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	int32  CharacterID = INDEX_NONE;

	UPROPERTY(EditDefaultsOnly, Category = "Skill")
	TSubclassOf<UGameplayAbility> AbilityClass;
};
