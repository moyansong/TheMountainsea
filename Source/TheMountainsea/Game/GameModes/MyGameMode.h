// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

class AMyGameState;

/**
 * 继承GameModeBase时，GameState也必须继承自GameStateBase
 */
UCLASS()
class THEMOUNTAINSEA_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY()
	AMyGameState* MyGameState;
};
