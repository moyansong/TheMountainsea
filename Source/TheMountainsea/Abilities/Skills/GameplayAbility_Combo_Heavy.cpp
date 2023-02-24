// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Combo_Heavy.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"

void UGameplayAbility_Combo_Heavy::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	AMyCharacter* MyCharacter = Cast<AMyCharacter>(ActorInfo->OwnerActor);
	if (MyCharacter && MyCharacter->GetCombatComponent())
	{
		FSimpleComboCheck* Combo = MyCharacter->GetSimpleComboInfo(MyCharacter->GetLastActiveSkill());
		PlayMontage(*FString::FromInt(Combo->ComboIndex - 1));
		Combo->Reset();
	}
}
