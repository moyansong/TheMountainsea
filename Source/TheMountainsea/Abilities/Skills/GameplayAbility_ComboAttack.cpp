// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_ComboAttack.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"

void UGameplayAbility_ComboAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;
	
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(ActorInfo->OwnerActor);
	if (MyCharacter && MyCharacter->GetCombatComponent())
	{
		if (FSimpleComboCheck* ComboAttack = MyCharacter->GetSimpleComboInfo(AbilityName))
		{
			ComboAttack->Pressed();
			PlayMontage(*FString::FromInt(ComboAttack->ComboIndex));
		}
	}
}

void UGameplayAbility_ComboAttack::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(ActorInfo->OwnerActor))
	{
		if (FSimpleComboCheck* ComboAttack = MyCharacter->GetSimpleComboInfo(AbilityName))
		{
			ComboAttack->Reset(); 
		}
	}
}
