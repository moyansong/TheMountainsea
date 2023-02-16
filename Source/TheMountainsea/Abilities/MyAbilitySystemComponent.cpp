// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "MyGameplayAbility.h"
#include "../Characters/MyCharacter.h"
#include "../Game/GameStates/MyGameState.h"

UMyAbilitySystemComponent::UMyAbilitySystemComponent()
{
}

void UMyAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

}

UMyAbilitySystemComponent* UMyAbilitySystemComponent::GetAbilitySystemComponentFromActor(const AActor* Actor, bool LookForComponent)
{
	return Cast<UMyAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor, LookForComponent));
}

void UMyAbilitySystemComponent::InitAbility()
{
	if (AMyGameState* MyGameState = GetWorld()->GetGameState<AMyGameState>())
	{
		int32 CharacterID = MyCharacter.IsValid() ? MyCharacter->GetCharacterID() : INDEX_NONE;
		TArray<FCharacterSkillTable*> SKillTables;
		MyGameState->GetCharacterSkillsTables(CharacterID, SKillTables);

		for (auto SkillTable : SKillTables)
		{
			AddAbility(SkillTable->AbilityClass);
		}
	}
}

void UMyAbilitySystemComponent::AddAbility(TSubclassOf<UGameplayAbility> NewAbilityClass)
{
	if (!NewAbilityClass) return;

	FGameplayAbilitySpecHandle Handle = GiveAbility(FGameplayAbilitySpec(NewAbilityClass));
	if (UMyGameplayAbility* Ability = Cast<UMyGameplayAbility>(NewAbilityClass->GetDefaultObject()))
	{
		Skills.Add(Ability->GetAbilityName(), Handle);
		if (Ability->IsComboAttack())
		{
			RegisterComboAttack(Ability->GetAbilityName());
		}
	}
}

void UMyAbilitySystemComponent::RegisterComboAttack(const FName& ComboName)
{
	FSimpleComboCheck ComboCheck;
	ComboCheck.ComboName = ComboName;
	ComboCheck.Character = MyCharacter.Get();

	UMyGameplayAbility* Ability = GetAbility(ComboName);
	ComboCheck.MaxIndex = Ability ? Ability->GetCompositeSectionsNumber() : 4;

	ComboChecks.Add(ComboName, ComboCheck);
}

UMyGameplayAbility* UMyAbilitySystemComponent::GetAbility(const FName& AbilityName)
{
	if (FGameplayAbilitySpecHandle* Handle = Skills.Find(AbilityName))
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(*Handle))
		{
			return Cast<UMyGameplayAbility>(Spec->Ability);
		}
	}
	return nullptr;
}

FGameplayAbilitySpecHandle UMyAbilitySystemComponent::GetSkill(const FName& SkillName)
{
	return *Skills.Find(SkillName);
}

FGameplayTag UMyAbilitySystemComponent::GetSkillTag(const FName& SkillName)
{
	if (UMyGameplayAbility* Ability = GetAbility(SkillName))
	{
		return Ability->AbilityTags.First();
	}
	return FGameplayTag();
}

FSimpleComboCheck* UMyAbilitySystemComponent::GetSimpleComboInfo(const FName& ComboName)
{
	return ComboChecks.Find(ComboName);
}

bool UMyAbilitySystemComponent::ActivateSkill(FName SkillName)
{
	return Skills.Contains(SkillName) ? TryActivateAbility(*Skills.Find(SkillName)) : false;
}

