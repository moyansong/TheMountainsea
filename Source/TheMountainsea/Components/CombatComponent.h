// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActorComponent.h"
#include "../Characters/CharacterTypes.h"
#include "GameplayEffectTypes.h"
#include "../TheMountainseaTypes.h"
#include "SimpleCombatTypes.h"
#include "CombatComponent.generated.h"

class UMyGameplayAbility;
class UMyAbilitySystemComponent;
class ADrawText;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEMOUNTAINSEA_API UCombatComponent : public UMyActorComponent
{
	GENERATED_BODY()

public:	
	friend class AMyCharacter;
	friend class APlayerCharacter;

	UCombatComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//------------------------------------------Set && Get---------------------------------------------------------
	void SetCharacterCombatState(ECharacterCombatState State);
	FORCEINLINE ECharacterCombatState GetCharacterCombatState() const { return CharacterCombatState; }

	UMyGameplayAbility* GetAbility(const FName& AbilityName);

	FSimpleComboCheck* GetSimpleComboInfo(const FName& ComboName);

	FName GetActiveSkill();
	void SetActiveSkill(const FName& SkillName);

	FORCEINLINE FName GetLastActiveSkill() const { return LastActiveSkill; }
	void SetLastActiveSkill(const FName& SkillName) { LastActiveSkill = SkillName; }

//------------------------------------------Functions---------------------------------------------------------
	UFUNCTION()
	void ComboPressed(const FName& ComboName);

	UFUNCTION()
	void ComboReleased(const FName& ComboName);

	UFUNCTION()
	void ComboReset(const FName& ComboName);
	
	UFUNCTION()
	void ActivateSkill(const FName& SkillName);

	void Dodge();

protected:
	virtual void BeginPlay() override;

	void OnCharacterCombatStateSet();

	virtual void OnManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnDamageChanged(const FOnAttributeChangeData& Data);

	void SpawnDamageText(float DamageAmount, const FVector& Location);

	void GetHit(const FHitData& HitData);

	void Die();

//---------------------------------------------RPC------------------------------------------------------------
	UFUNCTION(Server, Reliable)
	void ServerSetCharacterCombatState(ECharacterCombatState State);

	UFUNCTION(Server, Reliable)
	void ServerActivateSkill(const FName& SkillName);

	UFUNCTION(Server, Reliable)
	void ServerComboPressed(const FName& ComboName);

	UFUNCTION(Server, Reliable)
	void ServerComboReleased(const FName& ComboName);

	UFUNCTION(Server, Reliable)
	void ServerComboReset(const FName& ComboName);

	UFUNCTION(Client, Reliable)
	void ClientSpawnDamageText(float DamageAmount, const FVector_NetQuantize& Location);

//------------------------------------------Parameters---------------------------------------------------------

private:
	UPROPERTY()
	TWeakObjectPtr<UMyAbilitySystemComponent> MyAbilitySystemComponent;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterCombatState, VisibleAnywhere, Category = Parameter)
	ECharacterCombatState CharacterCombatState = ECharacterCombatState::ECCS_OutCombat;
	UFUNCTION()
	void OnRep_CharacterCombatState(ECharacterCombatState OldState);

	// 仅在释放时设置，在技能结束后不会重置，请使用GetAvtiveSkill
	FName ActiveSkill = NAME_None;
	FName LastActiveSkill = NAME_None;

	// 显示伤害数字的类
	UPROPERTY(EditAnywhere, Category = UI)
	TSubclassOf<ADrawText> DamageTextClass;

	UPROPERTY()
	FHitData MyHitData;
};
