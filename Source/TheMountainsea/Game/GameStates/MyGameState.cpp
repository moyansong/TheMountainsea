// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"

AMyGameState::AMyGameState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAnimTable(TEXT("/Game/Table/CharacterAnimTable"));
	CharacterAnimTablePtr = CharacterAnimTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterSkillTable(TEXT("/Game/Table/CharacterSkillTable"));
	CharacterSkillTablePtr = CharacterSkillTable.Object;

	static ConstructorHelpers::FObjectFinder<UDataTable> CharacterAttributeTable(TEXT("/Game/Table/CharacterAttributeTable"));
	CharacterAttributeTablePtr = CharacterAttributeTable.Object;
}

FCharacterAnimTable* AMyGameState::GetCharacterAnimTable(int32 ID)
{
	return GetTable(ID, CharacterAnimTablePtr, CharacterAnimTables, TEXT("AnimTable"));
}

TArray<FCharacterAnimTable*>* AMyGameState::GetCharacterAnimTables()
{
	return GetTables(CharacterAnimTablePtr, CharacterAnimTables, TEXT("AnimTable"));
}

FCharacterSkillTable* AMyGameState::GetCharacterSkillTable(int32 ID)
{
	return GetTable(ID, CharacterSkillTablePtr, CharacterSkillTables, TEXT("SkillTable"));
}

TArray<FCharacterSkillTable*>* AMyGameState::GetCharacterSkillTables()
{
	return GetTables(CharacterSkillTablePtr, CharacterSkillTables, TEXT("SkillTable"));
}

bool AMyGameState::GetCharacterSkillsTables(int32 ID, TArray<FCharacterSkillTable*>& OutSkillTables)
{
	if (TArray<FCharacterSkillTable*>* InCharacterSkillTables = GetCharacterSkillTables())
	{
		if (InCharacterSkillTables->FindByPredicate(
			[ID](const FCharacterSkillTable* InTmp)
			{return InTmp->CharacterID == ID; }))
		{
			for (auto& Tmp : *InCharacterSkillTables)
			{
				if (Tmp->CharacterID == ID)
				{
					OutSkillTables.Add(Tmp);
				}
			}
			return OutSkillTables.Num() > 0;
		}
	}
	return false;
}

FCharacterAttributeTable* AMyGameState::GetCharacterAttributeTable(int32 ID)
{
	return GetTable(ID, CharacterAttributeTablePtr, CharacterAttributeTables, TEXT("AttributeTable"));
}
