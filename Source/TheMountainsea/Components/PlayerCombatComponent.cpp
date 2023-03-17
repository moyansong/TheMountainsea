// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCombatComponent.h"
#include "../Game/PlayerControllers/UIPlayerController.h"

void UPlayerCombatComponent::OnManaChanged(const FOnAttributeChangeData& Data)
{
	Super::OnManaChanged(Data);

	if (MyPlayerController.IsValid() && IsLocallyControlled())
	{
		MyPlayerController->SetUIMana(Data.OldValue);
	}
}

void UPlayerCombatComponent::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	Super::OnHealthChanged(Data);

	if (MyPlayerController.IsValid() && IsLocallyControlled())
	{
		MyPlayerController->SetUIHealth(Data.OldValue);
	}
}

void UPlayerCombatComponent::OnDamageChanged(const FOnAttributeChangeData& Data)
{
	Super::OnDamageChanged(Data);
}
