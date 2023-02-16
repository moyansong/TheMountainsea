//Copyright (C) RenZhai.2022.All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterAttributeTable.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAttributeTable :public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	int32 CharacterID = INDEX_NONE;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	int32 Level = 1;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	float Health = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	float Mana = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	float PhysicalAttack = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	float MagicAttack = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	float PhysicalDefense = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterAttribute")
	float MagicDefense = 10.f;
};