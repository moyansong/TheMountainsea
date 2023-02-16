// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "../../DataTables/CharacterAnimTable.h"
#include "../../DataTables/CharacterSkillTable.h"
#include "../../DataTables/CharacterAttributeTable.h"
#include "MyGameState.generated.h"

class UDataTable;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMyGameState();

	FCharacterAnimTable* GetCharacterAnimTable(int32 ID);
	TArray<FCharacterAnimTable*>* GetCharacterAnimTables();

	FCharacterSkillTable* GetCharacterSkillTable(int32 ID);
	TArray<FCharacterSkillTable*>* GetCharacterSkillTables();

	bool GetCharacterSkillsTables(int32 ID, TArray<FCharacterSkillTable*>& OutSkillTables);

	FCharacterAttributeTable* GetCharacterAttributeTable(int32 ID);

	template<class T>
	TArray<T*>* GetTables(UDataTable* InTable, TArray<T*>& OutTables, const FString& MsgTag = TEXT("MyTable"))
	{
		if (!OutTables.Num())
		{
			if (InTable)
			{
				InTable->GetAllRows(MsgTag, OutTables);
			}
		}

		return &OutTables;
	}

	template<class T>
	T* GetTable(int32 InTableID, UDataTable* InTable, TArray<T*>& OutTables, const FString& MsgTag = TEXT("MyTable"))
	{
		if (TArray<T*>* InTables = GetTables<T>(InTable, OutTables, MsgTag))
		{
			if (InTables->Num())
			{
				if (auto Table = InTables->FindByPredicate([&](T* InMyTable) {return InMyTable->CharacterID == InTableID; }))
				{
					return *Table;
				}
			}
		}

		return nullptr;
	}

protected:
	UPROPERTY()
	UDataTable* CharacterAnimTablePtr;

	UPROPERTY()
	UDataTable* CharacterSkillTablePtr;

	UPROPERTY()
	UDataTable* CharacterAttributeTablePtr;

	TArray<FCharacterAnimTable*>  CharacterAnimTables;
	TArray<FCharacterSkillTable*> CharacterSkillTables;
	TArray<FCharacterAttributeTable*> CharacterAttributeTables;
};
