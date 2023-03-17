// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "SimpleDrawTextFunctionLibrary.h"
#include "Actor/DrawText.h"
#include "Components/CapsuleComponent.h"
#include "../TheMountainsea.h"
#include "../Characters/MyCharacter.h"
#include "../Abilities/MyGameplayAbility.h"
#include "../Abilities/MyAbilitySystemComponent.h"
#include "../Game/PlayerControllers/UIPlayerController.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCombatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UCombatComponent, CharacterCombatState, COND_SimulatedOnly);
}

void UCombatComponent::SetCharacterCombatState(ECharacterCombatState State)
{
	if (CharacterCombatState == State) return;

	CharacterCombatState = State;
	OnCharacterCombatStateSet();
	if (MyCharacter.IsValid() && !MyCharacter->HasAuthority())
	{
		ServerSetCharacterCombatState(State);
	}
}

UMyGameplayAbility* UCombatComponent::GetAbility(const FName& AbilityName)
{
	return MyAbilitySystemComponent.IsValid() ? MyAbilitySystemComponent->GetAbility(AbilityName) : nullptr;
}

FSimpleComboCheck* UCombatComponent::GetSimpleComboInfo(const FName& ComboName)
{
	return MyAbilitySystemComponent.IsValid() ? MyAbilitySystemComponent->GetSimpleComboInfo(ComboName) : nullptr;
}

FName UCombatComponent::GetActiveSkill()
{
	if (UMyGameplayAbility* Ability = GetAbility(ActiveSkill))
	{
		return Ability->IsActive() ? ActiveSkill : NAME_None;
	}
	return NAME_None;
}

void UCombatComponent::SetActiveSkill(const FName& SkillName)
{
	LastActiveSkill = ActiveSkill;
	ActiveSkill = SkillName;
}

void UCombatComponent::ServerSetCharacterCombatState_Implementation(ECharacterCombatState State)
{
	SetCharacterCombatState(State);
}

void UCombatComponent::OnRep_CharacterCombatState(ECharacterCombatState OldState)
{
	OnCharacterCombatStateSet();
}

void UCombatComponent::OnCharacterCombatStateSet()
{
	switch (CharacterCombatState)
	{
	case ECharacterCombatState::ECCS_OutCombat:
		break;
	case ECharacterCombatState::ECCS_InCombat:
		break;
	case ECharacterCombatState::ECCS_Dead:
		break;
	default:
		break;
	}
}

void UCombatComponent::ActivateSkill(const FName& SkillName)
{
	if (MyAbilitySystemComponent.IsValid())
	{
		MyAbilitySystemComponent->ActivateSkill(SkillName);
	}
}

void UCombatComponent::ServerActivateSkill_Implementation(const FName& SkillName)
{
	ActivateSkill(SkillName);
}

void UCombatComponent::Dodge()
{
	ActivateSkill(TEXT("Dodge"));
}

void UCombatComponent::ComboPressed(const FName& ComboName)
{
	if (FSimpleComboCheck* ComboCheck = GetSimpleComboInfo(ComboName))
	{
		ComboCheck->Pressed();
	}
}

void UCombatComponent::ComboReleased(const FName& ComboName)
{
	if (FSimpleComboCheck* ComboCheck = GetSimpleComboInfo(ComboName))
	{
		ComboCheck->Released();
		if (GetActiveSkill() != ComboName)
		{
			ComboCheck->Reset();
		}
	}
}

void UCombatComponent::ComboReset(const FName& ComboName)
{
	if (FSimpleComboCheck* ComboCheck = GetSimpleComboInfo(ComboName))
	{
		ComboCheck->Reset();
	}
}

void UCombatComponent::ServerComboPressed_Implementation(const FName& ComboName)
{
	ComboPressed(ComboName);
}

void UCombatComponent::ServerComboReleased_Implementation(const FName& ComboName)
{
	ComboReleased(ComboName);
}

void UCombatComponent::ServerComboReset_Implementation(const FName& ComboName)
{
	ComboReset(ComboName);
}

void UCombatComponent::OnManaChanged(const FOnAttributeChangeData& Data)
{
	
}

void UCombatComponent::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	
}

void UCombatComponent::OnDamageChanged(const FOnAttributeChangeData& Data)
{	
	const FGameplayEffectModCallbackData* GEModData = Data.GEModData;// 这个数据只有服务器有
	if (GEModData)
	{
		FGameplayEffectContextHandle Context = GEModData->EffectSpec.GetContext();
		UAbilitySystemComponent* SourceAbilitySystemComponent = Context.GetOriginalInstigatorAbilitySystemComponent();
		AActor* InstigatorActor = SourceAbilitySystemComponent->AbilityActorInfo.IsValid() ? SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get() : nullptr;

		AMyCharacter* InstigatorCharacter = Cast<AMyCharacter>(InstigatorActor);
		if (InstigatorCharacter && InstigatorCharacter->GetCombatComponent())
		{
			InstigatorCharacter->GetCombatComponent()->ClientSpawnDamageText(Data.NewValue, GetOwnerLocation());
		}
		// 不在本地直接Spawn的原因是当伤害值和之前一次伤害相同时不会复制
		ClientSpawnDamageText(-Data.NewValue, GetOwnerLocation());
	}
}

void UCombatComponent::SpawnDamageText(float DamageAmount, const FVector& Location)
{
	if (DamageTextClass)
	{
		USimpleDrawTextFunctionLibrary::SpawnDrawTextByClass(
			GetWorld(),
			DamageTextClass,
			Location + FVector(0.f, 0.f, 120.f),
			FString::Printf(TEXT("%.1lf"), DamageAmount),
			FColor::Red,
			0.8f
		);
	}
}

void UCombatComponent::ClientSpawnDamageText_Implementation(float DamageAmount, const FVector_NetQuantize& Location)
{
	SpawnDamageText(DamageAmount, Location);
}

void UCombatComponent::GetHit(const FHitData& HitData)
{
	MyHitData = HitData;
	EHitType HitType = HitData.HitType;
	switch (HitType)
	{
	case EHitType::EHT_None:
		break;
	case EHitType::EHT_SlightHit:
		ActivateSkill("SlightHit");
		break;
	case EHitType::EHT_HeavyHit:
		ActivateSkill("HeavyHit");
		break;
	}
}

void UCombatComponent::Die()
{
	if (MyCharacter.IsValid())
	{
		MyCharacter->SetOverheadWidgetVisibility(false);
		if (MyCharacter->GetCapsuleComponent())
		{
			MyCharacter->GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
			MyCharacter->GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
		}
	}
}


