// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Random.h"
#include "../../Characters/MyCharacter.h"

void UGameplayAbility_Random::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(ActorInfo->OwnerActor))
	{
		PlayMontage(*FString::FromInt(FMath::RandRange(0, GetCompositeSectionsNumber() - 1)));
	}
}
