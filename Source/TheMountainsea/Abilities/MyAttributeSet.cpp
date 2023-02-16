// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "../Characters/MyCharacter.h"
#include "../TheMountainsea.h"
#include "../Game/GameStates/MyGameState.h"

UMyAttributeSet::UMyAttributeSet() : 
	Level(1),
	Health(100.f), 
	MaxHealth(100.f), 
	Mana(100.f), 
	MaxMana(100.f),
	Damage(0.f),
	PhysicalAttack(10.f),
	MagicAttack(0.f),
	PhysicalDefense(10.f),
	MagicDefense(0.f)
{
}

void UMyAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMyAttributeSet, Level);
	DOREPLIFETIME(UMyAttributeSet, Health);
	DOREPLIFETIME(UMyAttributeSet, MaxHealth);
	DOREPLIFETIME(UMyAttributeSet, Mana);
	DOREPLIFETIME(UMyAttributeSet, MaxMana);
	DOREPLIFETIME(UMyAttributeSet, Damage);
	DOREPLIFETIME(UMyAttributeSet, PhysicalAttack);
	DOREPLIFETIME(UMyAttributeSet, MagicAttack);
	DOREPLIFETIME(UMyAttributeSet, PhysicalDefense);
	DOREPLIFETIME(UMyAttributeSet, MagicDefense);
}

void UMyAttributeSet::InitAttribute()
{
	if (AMyGameState* MyGameState = GetWorld()->GetGameState<AMyGameState>())
	{
		if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(GetOwningActor()))
		{
			if (FCharacterAttributeTable* AttributeTable = MyGameState->GetCharacterAttributeTable(MyCharacter->GetCharacterID()))
			{
				SetLevel(AttributeTable->Level); 
				SetHealth(AttributeTable->Health);
				SetMaxHealth(AttributeTable->Health);
				SetMana(AttributeTable->Mana);
				SetMaxMana(AttributeTable->Mana);
				SetPhysicalAttack(AttributeTable->PhysicalAttack);
				SetMagicAttack(AttributeTable->MagicAttack);
				SetPhysicalDefense(AttributeTable->PhysicalDefense);
				SetMagicDefense(AttributeTable->MagicDefense);
			}
		}
	}
}

float UMyAttributeSet::GetOldValue(float Value, float Magnitude, EGameplayModOp::Type ModOp)
{
	switch (ModOp)
	{
	case EGameplayModOp::Type::Additive:
		return Value - Magnitude;
		break;
	case EGameplayModOp::Type::Division:
		return Value * Magnitude;
		break;
	case EGameplayModOp::Type::Max:
		break;
	case EGameplayModOp::Type::Multiplicitive:
		return Value / Magnitude;
		break;
	case EGameplayModOp::Type::Override:
		break;
	}
	return 0.f;
}

void UMyAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
}

void UMyAttributeSet::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComponent = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComponent)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComponent->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

void UMyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		HandleManaChanged(Data);
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		HandleHealthChanged(Data);
	}
	else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		HandleDamageChanged(Data);
	}
}

void UMyAttributeSet::HandleManaChanged(const FGameplayEffectModCallbackData& Data)
{
	float Magnitude = Data.EvaluatedData.Magnitude;
	EGameplayModOp::Type ModOp = Data.EvaluatedData.ModifierOp;

	const float OldMana = GetOldValue(GetMana(), Magnitude, ModOp);
	SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));

}

void UMyAttributeSet::HandleHealthChanged(const FGameplayEffectModCallbackData& Data)
{
	float Magnitude = Data.EvaluatedData.Magnitude;
	EGameplayModOp::Type ModOp = Data.EvaluatedData.ModifierOp;

	const float OldHealth = GetOldValue(GetHealth(), Magnitude, ModOp);
	SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

}

void UMyAttributeSet::HandleDamageChanged(const FGameplayEffectModCallbackData& Data)
{
	const float OldHealth = GetHealth();
	float DamageToCause = GetDamage();
	float NewHealth = FMath::Clamp(OldHealth - DamageToCause, 0.f, GetMaxHealth());
	SetHealth(NewHealth);

}

void UMyAttributeSet::OnRep_Level(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Level, OldValue);
}

void UMyAttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Health, OldValue);
}

void UMyAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxHealth, OldValue);
}

void UMyAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Mana, OldValue);
}

void UMyAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MaxMana, OldValue);
}

void UMyAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, Damage, OldValue);
}

void UMyAttributeSet::OnRep_PhysicalAttack(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, PhysicalAttack, OldValue);
}

void UMyAttributeSet::OnRep_MagicAttack(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MagicAttack, OldValue);
}

void UMyAttributeSet::OnRep_PhysicalDefense(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, PhysicalDefense, OldValue);
}

void UMyAttributeSet::OnRep_MagicDefense(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMyAttributeSet, MagicDefense, OldValue);
}

