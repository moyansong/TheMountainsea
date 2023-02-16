// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Skill.h"
#include "GameplayAbility_Random.generated.h"

/**
 * 随机播放蒙太奇中的一个Section
 */
UCLASS()
class THEMOUNTAINSEA_API UGameplayAbility_Random : public UGameplayAbility_Skill
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
};
