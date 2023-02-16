// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttributeWidget.h"
#include "../../BaseWidgets/BarText.h"

void UPlayerAttributeWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerAttributeWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerAttributeWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UPlayerAttributeWidget::SetMana(float Mana, float MaxMana)
{
	if (ManaBarText)
	{
		ManaBarText->SetValue(Mana, MaxMana);
	}
}

void UPlayerAttributeWidget::SetHealth(float Health, float MaxHealth)
{
	if (HealthBarText)
	{
		HealthBarText->SetValue(Health, MaxHealth);
	}
}

