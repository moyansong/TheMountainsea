// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../MyUserWidget.h"
#include "PlayerAttributeWidget.generated.h"

class UBarText;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UPlayerAttributeWidget : public UMyUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

//---------------------------------------Functions---------------------------------------------------------------------
	void SetMana(float Mana, float MaxMana);
	void SetHealth(float Health, float MaxHealth);

//---------------------------------------Parameters---------------------------------------------------------------------

	UPROPERTY(meta = (BindWidget))
	UBarText* HealthBarText;

	UPROPERTY(meta = (BindWidget))
	UBarText* ManaBarText;
};
