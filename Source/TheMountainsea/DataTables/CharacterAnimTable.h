// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "CharacterAnimTable.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct  FCharacterAnimTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterAnimTable();

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	int32  CharacterID = INDEX_NONE;

};
