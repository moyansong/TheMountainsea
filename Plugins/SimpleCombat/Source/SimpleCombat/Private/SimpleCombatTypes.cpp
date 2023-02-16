//Copyright (C) RenZhai.2022.All Rights Reserved.
#include "SimpleCombatTypes.h"
#include "Interfaces/SimpleCombatInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

FSimpleComboCheck::FSimpleComboCheck() : 
	ComboIndex(INDEX_NONE),
	bLongPressed(false),
	bShortPressed(false),
	Character(nullptr),
	MaxIndex(0)
{
}

void FSimpleComboCheck::UpdateComboIndex()
{
	check(MaxIndex > 0);

	++ComboIndex;
	if (ComboIndex > MaxIndex)
	{
		ComboIndex = 1;
	}
}

void FSimpleComboCheck::Pressed()
{
	if (ComboIndex == INDEX_NONE)
	{
		PressDelegate.ExecuteIfBound();
		++ComboIndex;

		check(Character);

		if (Character)
		{
			Character->ComboShortPressed(ComboName);
		}
	}

	bShortPressed = true;// 短按的释放在动画通知AmimNotifyState_CheckCombo里
	bLongPressed = true;
}

void FSimpleComboCheck::Released()
{
	bLongPressed = false;
}

void FSimpleComboCheck::Reset()
{
	ComboIndex = INDEX_NONE;
}
