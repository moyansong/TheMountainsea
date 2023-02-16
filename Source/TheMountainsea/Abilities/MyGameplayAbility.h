// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MyGameplayAbility.generated.h"

class UAbilityTask_PlayMontage;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UMyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
//------------------------------------------Set && Get---------------------------------------------------------
	FORCEINLINE FName GetAbilityName() const { return AbilityName; }

	FORCEINLINE bool IsComboAttack() const { return bIsComboAttack; }

	// 获取技能蒙太奇有多少个Section
	int32 GetCompositeSectionsNumber();

//------------------------------------------Functions---------------------------------------------------------
	UMyGameplayAbility();

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility", meta = (DisplayName = "PlayMontage"))
	UAbilityTask_PlayMontage* CreatePlayMontageTask(
			FName TaskInstanceName,
			UAnimMontage* InMontageToPlay,
			float Rate = 1.f,
			FName StartSection = NAME_None,
			bool bStopWhenAbilityEnds = true,
			float AnimRootMotionTranslationScale = 1.f,
			float StartTimeSeconds = 0.f
	);

	UFUNCTION(BlueprintCallable, Category = "GameplayAbility")
	UAbilityTask_PlayMontage* PlayMontage(FName StartSection = NAME_None);

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnBlendOut", meta = (ScriptName = "OnBlendOut"))
	void K2_OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCompleted", meta = (ScriptName = "OnCompleted"))
	void K2_OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnCancelled", meta = (ScriptName = "OnCancelled"))
	void K2_OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION(BlueprintImplementableEvent, Category = Ability, DisplayName = "OnInterrupted", meta = (ScriptName = "OnInterrupted"))
	void K2_OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData);

protected:
	UFUNCTION()
	virtual	void OnBlendOut(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	virtual	void OnCompleted(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	virtual	void OnCancelled(FGameplayTag EventTag, FGameplayEventData EventData);

	UFUNCTION()
	virtual	void OnInterrupted(FGameplayTag EventTag, FGameplayEventData EventData);

	// 被动调用该Ability时会执行的事件(SendGameplayEventToActor来触发，然后根据Tag找到对应能力)，例如被打播放飞出去的蒙太奇
	UFUNCTION()
	virtual	void OnGameplayEvent(FGameplayTag EventTag, FGameplayEventData EventData);

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData
	) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateEndAbility, 
		bool bWasCancelled
	) override;

	virtual void CancelAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		bool bReplicateCancelAbility
	) override;

//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = Montage)
	UAnimMontage* AbilityMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = GameplayEffects)
	TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> EffectMap;

	UPROPERTY(EditAnywhere, Category = Parameter)
	FName AbilityName;

	UPROPERTY(EditDefaultsOnly, Category = Parameter)
	bool bIsComboAttack;

private:

};
