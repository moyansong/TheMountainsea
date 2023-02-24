// Fill out your copyright notice in the Description page of Project Settings.


#include "UIPlayerController.h"
#include "../../UI/MyHUD.h"
#include "../../UI/Main/GameMainWidget.h"
#include "../../TheMountainsea.h"
#include "../../UI/Attribute/Player/PlayerAttributeWidget.h"
#include "../../Abilities/MyAttributeSet.h"
#include "../../Characters/PlayerCharacters/PlayerCharacter.h"

AUIPlayerController::AUIPlayerController()
{
}

void AUIPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUIPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (MyPlayerCharacter.IsValid())
	{
		MyPlayerCharacter->PossessedBy(this);
		MyAttributeSet = MyPlayerCharacter->GetAttributeSet();
		if (MyAttributeSet.IsValid())
		{
			SetUIMana();
			SetUIHealth();
		}
	}
}

void AUIPlayerController::AcknowledgePossession(APlayerCharacter* NewCharacter)
{
	Super::AcknowledgePossession(NewCharacter);

	if (MyPlayerCharacter.IsValid())
	{
		MyAttributeSet = MyPlayerCharacter->GetAttributeSet();
	}
}

void AUIPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AUIPlayerController::SetUIMana(float OldMana)
{
	if (HUD.IsValid() && HUD->GameMainWidget && HUD->GameMainWidget->PlayerAttributeWidget)
	{
		const float Mana = MyAttributeSet.IsValid() ? MyAttributeSet->GetMana() : 0.f;
		const float MaxMana = MyAttributeSet.IsValid() ? MyAttributeSet->GetMaxMana() : 0.f; 
		HUD->GameMainWidget->PlayerAttributeWidget->SetMana(Mana, MaxMana);
	}
}

void AUIPlayerController::SetUIHealth(float OldHealth)
{
	if (HUD.IsValid() && HUD->GameMainWidget && HUD->GameMainWidget->PlayerAttributeWidget)
	{
		const float Health = MyAttributeSet.IsValid() ? MyAttributeSet->GetHealth() : 0.f;
		const float MaxHealth = MyAttributeSet.IsValid() ? MyAttributeSet->GetMaxHealth() : 0.f;
		HUD->GameMainWidget->PlayerAttributeWidget->SetHealth(Health, MaxHealth);
	}
}
