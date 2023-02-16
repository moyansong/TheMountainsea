// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../SimpleCombatTypes.h"
#include "SimpleCombatInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, meta = (CannotImplementInterfaceInBlueprint))
class USimpleCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SIMPLECOMBAT_API ISimpleCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void AnimSignal(EAnimSignalType AnimSignalType) {}

	// 在动画通知CheckCombo/FSimpleComboCheck::Pressed()Pressed里调用
	UFUNCTION(Blueprintable, Category = "Combat")
	virtual void ComboShortPressed(const FName& ComboName) {}

	// 在动画通知CheckCombo/FSimpleComboCheck::Pressed()Pressed里调用
	UFUNCTION(Blueprintable, Category = "Combat")
	virtual void ComboLongPressed(const FName& ComboName) {}

	virtual struct FSimpleComboCheck* GetSimpleComboInfo(const FName& ComboName) { return nullptr; }
};
