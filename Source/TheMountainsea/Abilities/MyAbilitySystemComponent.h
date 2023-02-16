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
//------------------------------------------Set && Get---------------------------------------------------------
	UMyGameplayAbility* GetAbility(const FName& AbilityName);
	
	FGameplayAbilitySpecHandle GetSkill(const FName& SkillName);

	FGameplayTag GetSkillTag(const FName& SkillName);

	// 获取FSimpleComboCheck
	FSimpleComboCheck* GetSimpleComboInfo(const FName& ComboName);

//------------------------------------------Functions---------------------------------------------------------
	void InitAbility();

	void AddAbility(TSubclassOf<UGameplayAbility> NewAbilityClass);

	bool ActivateSkill(FName SkillName);

	static UMyAbilitySystemComponent* GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent = false);

protected:
	virtual void BeginPlay() override;

	void RegisterComboAttack(const FName& ComboName);

//------------------------------------------Parameters---------------------------------------------------------

private:
	UPROPERTY()
	TWeakObjectPtr<AMyCharacter> MyCharacter;

	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<UMyGameplayAbility>> AbilityClasses;

	// 存储所有技能，包括Combo
	TMap<FName, FGameplayAbilitySpecHandle> Skills;

	// 存储FSimpleComboCheck
	TMap<FName, FSimpleComboCheck> ComboChecks;
};
