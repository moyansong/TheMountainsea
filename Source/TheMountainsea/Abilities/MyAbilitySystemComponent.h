// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SimpleCombatTypes.h"
#include "MyAbilitySystemComponent.generated.h"

class UMyGameplayAbility;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UMyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	friend class AMyCharacter;
	UMyAbilitySystemComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
//------------------------------------------Set && Get---------------------------------------------------------
	UMyGameplayAbility* GetAbility(const FName& AbilityName);
	
	FGameplayAbilitySpecHandle GetSkill(const FName& SkillName);

	FGameplayTag GetSkillTag(const FName& SkillName);

	// 获取FSimpleComboCheck
	FSimpleComboCheck* GetSimpleComboInfo(const FName& ComboName);

//------------------------------------------Functions---------------------------------------------------------
	void InitAbility();

	void LocalInitAbility();

	void AddAbility(TSubclassOf<UGameplayAbility> NewAbilityClass);

	bool ActivateSkill(FName SkillName);

	static UMyAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

	virtual void OnRep_ActivateAbilities() override;

protected:
	virtual void BeginPlay() override;

	void RegisterComboAttack(const FName& ComboName);

//------------------------------------------Parameters---------------------------------------------------------

private:
	UPROPERTY()
	TWeakObjectPtr<AMyCharacter> MyCharacter;

	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<UMyGameplayAbility>> AbilityClasses;

	// 存储所有技能，包括Combo，在主控端和服务器都有
	TMap<FName, FGameplayAbilitySpecHandle> Skills;

	// 存储FSimpleComboCheck，在主控端和服务器都有
	TMap<FName, FSimpleComboCheck> ComboChecks;
};
