// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class AMyCharacter;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UMyAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Level)
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Level)
	
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxHealth)

	// 蓝条
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MaxMana)

	// 技能可以不调整Health，直接设置需要造成的Damage，方便用户自定义一些数学运算，记得将其设为override
	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_PhysicalAttack)
	FGameplayAttributeData PhysicalAttack;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, PhysicalAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MagicAttack)
	FGameplayAttributeData MagicAttack;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MagicAttack)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_PhysicalDefense)
	FGameplayAttributeData PhysicalDefense;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, PhysicalDefense)

	UPROPERTY(BlueprintReadOnly, Category = "Attribute", ReplicatedUsing = OnRep_MagicDefense)
	FGameplayAttributeData MagicDefense;
	ATTRIBUTE_ACCESSORS(UMyAttributeSet, MagicDefense)

//------------------------------------------Functions---------------------------------------------------------
	void InitAttribute();

	float GetOldValue(float Value, float Magnitude, EGameplayModOp::Type ModOp);
	
	// 属性修改前调用的函数，更多是是用来更改最大值的，例如NewValue = NewMaxHealth，然后把Health等比例放大
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// 属性改变后要做的工作，例如改变UI等，只在Server发生,这个函数结束后变量会复制到客户端
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	/** 此函数用于在属性的关联最大属性更改时按比例调整属性的值。（即，当MaxHealth增加时，Health增加的百分比与之前相同) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

protected:
	void HandleManaChanged(const FGameplayEffectModCallbackData& Data);
	void HandleHealthChanged(const FGameplayEffectModCallbackData& Data);
	void HandleDamageChanged(const FGameplayEffectModCallbackData& Data);

	UFUNCTION()
	virtual void OnRep_Level(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicalAttack(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicAttack(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicalDefense(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDefense(const FGameplayAttributeData& OldValue);

private:

};
