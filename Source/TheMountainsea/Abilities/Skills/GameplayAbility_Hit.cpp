// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility_Hit.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"

void UGameplayAbility_Hit::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) return;

	if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(ActorInfo->OwnerActor))
	{
		FHitData HitData = MyCharacter->GetHitData();
		if (HitData.InstigatorCharacter.IsValid())
		{
			switch (MyCharacter->GetReliativeLocation(HitData.InstigatorCharacter->GetActorLocation()))
			{
			case ERelativeLocation::ERL_Front:
				PlayMontage(TEXT("Front"));
				break;
			case ERelativeLocation::ERL_Back:
				PlayMontage(TEXT("Back"));
				break;
			case ERelativeLocation::ERL_Left:
				PlayMontage(TEXT("Left")); 
				break;
			case ERelativeLocation::ERL_Right:
				PlayMontage(TEXT("Right")); 
				break;
			default:
				break;
			}
		}
	}
}
