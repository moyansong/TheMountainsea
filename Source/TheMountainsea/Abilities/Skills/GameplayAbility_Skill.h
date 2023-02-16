// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyGameplayAbility.h"
#include "GameplayAbility_Skill.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UGameplayAbility_Skill : public UMyGameplayAbility
{
	GENERATED_BODY()

public:
	virtual	void OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData) override;

	virtual	void OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData) override;
};
