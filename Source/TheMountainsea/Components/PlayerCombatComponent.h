// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatComponent.h"
#include "PlayerCombatComponent.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UPlayerCombatComponent : public UCombatComponent
{
	GENERATED_BODY()
	
protected:
	virtual void OnManaChanged(const FOnAttributeChangeData& Data) override;
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data) override;
	virtual void OnDamageChanged(const FOnAttributeChangeData& Data) override;
};
