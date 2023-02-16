// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayAbility.h"
#include "MyAbilitySystemComponent.h"
#include "../TheMountainsea.h"
#include "../Characters/MyCharacter.h"
#include "../Components/CombatComponent.h"
#include "Tasks/AbilityTask_PlayMontage.h"

UMyGameplayAbility::UMyGameplayAbility()
{

}

int32 UMyGameplayAbility::GetCompositeSectionsNumber()
{
	return AbilityMontage ? AbilityMontage->CompositeSections.Num() : 0;
}

void UMyGameplayAbility::OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData)
{
	K2_OnBlendOut(EventTag, EventData);
}

void UMyGameplayAbility::OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	K2_OnCompleted(EventTag, EventData);
}

void UMyGameplayAbility::OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData)
{
	K2_OnCancelled(EventTag, EventData);
}

void UMyGameplayAbility::OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData)
{
	K2_OnInterrupted(EventTag, EventData);
}

void UMyGameplayAbility::OnGameplayEvent(FGameplayTag EventTag, FGameplayEventData EventData)
{
	// 创建目标数组
	FGameplayAbilityTargetData_ActorArray* NewTargetData_ActorArray = new FGameplayAbilityTargetData_ActorArray();
	NewTargetData_ActorArray->TargetActorArray.Add(const_cast<AActor*>(EventData.Target));
	
	FGameplayAbilityTargetDataHandle TargetHandleData;
	TargetHandleData.Add(NewTargetData_ActorArray);

	// 这里简单的把这个GA的所有GE都施加给Target了
	// 可以考虑针对不同的Tag施加不同的GE
	for (auto& EffectPair : EffectMap)
	{
		FGameplayEffectSpecHandle NewHandle = MakeOutgoingGameplayEffectSpec(EffectPair.Value, 1);

		if (NewHandle.IsValid())
		{
			// 获取GA实例
			FGameplayAbilitySpec* AbilitySpec = GetAbilitySystemComponentFromActorInfo()->FindAbilitySpecFromHandle(CurrentSpecHandle);
			if (AbilitySpec)
			{
				// 把GA的信息应用到GE上，例如把GA的标签打在GE上
				ApplyAbilityTagsToGameplayEffectSpec(*NewHandle.Data.Get(), AbilitySpec);
				NewHandle.Data->SetByCallerTagMagnitudes = AbilitySpec->SetByCallerTagMagnitudes;
			}
		}

		TArray<FActiveGameplayEffectHandle>  ActiveGameplayEffectHandles = ApplyGameplayEffectSpecToTarget(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, NewHandle, TargetHandleData);
	}
}

void UMyGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	// ActiveAbility最好完全重载，不要调父类的
	// Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bHasBlueprintActivate)
	{
		// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
		K2_ActivateAbility();
	}
	else if (bHasBlueprintActivateFromEvent)
	{
		if (TriggerEventData)
		{
			// A Blueprinted ActivateAbility function must call CommitAbility somewhere in its execution chain.
			K2_ActivateAbilityFromEvent(*TriggerEventData);
		}
		else
		{
			UE_LOG(LogAbilitySystem, Warning, TEXT("Ability %s expects event data but none is being supplied. Use Activate Ability instead of Activate Ability From Event."), *GetName());
			bool bReplicateEndAbility = false;
			bool bWasCancelled = true;
			EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
		}
	}// 这些都是蓝图逻辑
	else
	{
		if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
		{
			return;
		}

		AMyCharacter* MyCharacter = Cast<AMyCharacter>(ActorInfo->OwnerActor);
		if (MyCharacter)
		{
			PlayMontage();
		}
	}
}

void UMyGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	// EndAbility将销毁Ability
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UMyGameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);
}

UAbilityTask_PlayMontage* UMyGameplayAbility::CreatePlayMontageTask(FName TaskInstanceName, UAnimMontage* InMontageToPlay, float Rate, FName StartSection, bool bStopWhenAbilityEnds, float AnimRootMotionTranslationScale, float StartTimeSeconds)
{
	UAbilityTask_PlayMontage* Task = UAbilityTask_PlayMontage::PlayMontage(
		this,
		TaskInstanceName,
		InMontageToPlay,
		AbilityTags,
		Rate,
		StartSection,
		bStopWhenAbilityEnds,
		AnimRootMotionTranslationScale
	);

	if (Task)
	{
		Task->OnBlendOut.AddDynamic(this, &UMyGameplayAbility::OnBlendOut);
		Task->OnCompleted.AddDynamic(this, &UMyGameplayAbility::OnCompleted);
		Task->OnCancelled.AddDynamic(this, &UMyGameplayAbility::OnCancelled);
		Task->OnInterrupted.AddDynamic(this, &UMyGameplayAbility::OnInterrupted);
		Task->EventReceived.AddDynamic(this, &UMyGameplayAbility::OnGameplayEvent);

		Task->Activate();

		return Task;
	}

	return nullptr;
}

UAbilityTask_PlayMontage* UMyGameplayAbility::PlayMontage(FName StartSection)
{
	return CreatePlayMontageTask(NAME_None, AbilityMontage, 1.f, StartSection);
}