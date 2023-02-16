// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystemInterface.h"
#include "CharacterTypes.h"
#include "SimpleCombatTypes.h"
#include "GameplayEffectTypes.h"
#include "Interfaces/SimpleCombatInterface.h"
#include "../DataTables/CharacterAnimTable.h"
#include "../DataTables/CharacterSkillTable.h"
#include "../Interfaces/HitInterface.h"
#include "../Items/ItemTypes.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AController;
class AItem;
class AWeapon;
class UAnimMontage;
class UMotionComponent;
class UCombatComponent;
class UEquipmentComponent;
class UOverheadWidgetComponent;
class UMyAbilitySystemComponent;
class USoundBase;
class UParticleSystem;
class UMyGameplayAbility;
class UMyAttributeSet;

UCLASS()
class THEMOUNTAINSEA_API AMyCharacter : 
	public ACharacter, 
	public IHitInterface, 
	public ISimpleCombatInterface, 
	public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMyCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
//------------------------------------------Set && Get---------------------------------------------------------
	virtual USpringArmComponent* GetCameraBoom() const { return nullptr; }
	virtual UCameraComponent* GetFollowCamera() const { return nullptr; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	FORCEINLINE UMyAttributeSet* GetAttributeSet() const { return MyAttributeSet; }
	FORCEINLINE UCombatComponent* GetCombatComponent() const { return CombatComponent; }
	FORCEINLINE UMotionComponent* GetMotionComponent() const { return MotionComponent; }
	FORCEINLINE UEquipmentComponent* GetEquipmentComponent() const { return EquipmentComponent; }
	//FORCEINLINE UMyAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent; }
	FORCEINLINE UOverheadWidgetComponent* GetOverheadWidgetComponent() const { return OverheadWidgetComponent; }
	
	void SetCharacterState(ECharacterState State);
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

	void SetCharacterMotionState(ECharacterMotionState State);
	ECharacterMotionState GetCharacterMotionState() const;

	void SetCharacterCombatState(ECharacterCombatState State);
	ECharacterCombatState GetCharacterCombatState() const;

	ERelativeLocation GetReliativeLocation(const FVector& Location);

	FORCEINLINE int32 GetCharacterID() const { return CharacterID; }
	FORCEINLINE ECharacterType GetCharacterType() const { return CharacterType; }

	FName GetMontageCurrentSection(const UAnimMontage* Montage);

	AWeapon* GetWeapon() const;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollision(bool bCanWeaponHit);

	void SetOverheadWidgetVisibility(bool bVisibility);

	// 获取FSimpleComboCheck
	virtual FSimpleComboCheck* GetSimpleComboInfo(const FName& ComboName) override;

	float GetHealth() const;

	bool IsAlive() const;

	FHitData GetHitData() const;

	FGameplayTag GetSkillTag(const FName& SkillName) const ;

//------------------------------------------Functions---------------------------------------------------------
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void AnimSignal(EAnimSignalType AnimSignalType) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, DisplayName = "AnimSignal", Category = "AnimEvent")
	void K2_AnimSignal(EAnimSignalType AnimSignalType);

	// 只会在服务器激活技能，在客户端的话会发送RPC
	UFUNCTION(BlueprintCallable)
	virtual void ActivateSkill(const FName& SkillName);

	void AddAbility(TSubclassOf<UGameplayAbility> NewAbilityClass);

	// 在服务器和本地都会调用
	virtual void ComboShortPressed(const FName& ComboName) override;
	virtual void ComboLongPressed(const FName& ComboName) override;

	UFUNCTION()
	virtual void Fly();

	UFUNCTION()
	virtual void Dodge();

	// 以下几个函数在所有端都能收到
	virtual void OnManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnDamageChanged(const FOnAttributeChangeData& Data);

	// 只在服务器调用
	virtual void GetHit(const FHitData& HitData) override;

protected:
	virtual void BeginPlay() override;

	// 在Tick里进行，多用于第一次获取某个变量时执行某些事件
	virtual void Init();

	virtual void Die();

	void OnCharacterStateSet();

//---------------------------------------------RPC------------------------------------------------------------
	UFUNCTION(Server, Reliable)
	void ServerSetCharacterState(ECharacterState State);

//------------------------------------------Parameters---------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, Category = Parameter)
	int32 CharacterID = INDEX_NONE;

	UPROPERTY(EditDefaultsOnly, Category = Parameter)
	ECharacterType CharacterType = ECharacterType::ECT_NONE;
	
	UPROPERTY(ReplicatedUsing = OnRep_CharacterState, VisibleAnywhere, Category = Parameter)
	ECharacterState CharacterState = ECharacterState::ECS_OutCombat;
	UFUNCTION()
	void OnRep_CharacterState(ECharacterState OldState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Abilities)
	TObjectPtr<UMyAttributeSet> MyAttributeSet;

private:	
//-----------------------------------------Components---------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Component)
	TObjectPtr<UCombatComponent> CombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Component)
	TObjectPtr<UMotionComponent> MotionComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Component)
	TObjectPtr<UEquipmentComponent> EquipmentComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Component)
	TObjectPtr<UOverheadWidgetComponent> OverheadWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Component)
	TObjectPtr<UMyAbilitySystemComponent> AbilitySystemComponent;
};
