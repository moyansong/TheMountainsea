// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Skill.h"
#include "../../TheMountainsea.h"

void UGameplayAbility_Skill::OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnBlendOut(EventTag, EventData);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Skill::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnCompleted(EventTag, EventData);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Skill::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnCancelled(EventTag, EventData);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Skill::OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	Super::OnInterrupted(EventTag, EventData);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
