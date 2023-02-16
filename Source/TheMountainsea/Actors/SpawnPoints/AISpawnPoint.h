// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AISpawnPoint.generated.h"

class AAICharacter;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API AAISpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
	
public:
	AAISpawnPoint();
	virtual void Tick(float DeltaTime) override;

//------------------------------------------Functions---------------------------------------------------------

protected:
	virtual void BeginPlay() override;

	void SpawnAICharacter(int32 CharacterID, int32 Level = 1);

//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = Parameter)
	TSubclassOf<AAICharacter> AICharacterClass;

	UPROPERTY(EditAnywhere, Category = Parameter)
	int32 CharacterLevel = 1;
};
