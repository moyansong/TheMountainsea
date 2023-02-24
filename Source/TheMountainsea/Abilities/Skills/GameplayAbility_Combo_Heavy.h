// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Skill.h"
#include "GameplayAbility_Combo_Heavy.generated.h"

/**
 * Combo的重击，长按时触发
 */
UCLASS()
class THEMOUNTAINSEA_API UGameplayAbility_Combo_Heavy : public UGameplayAbility_Skill
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
