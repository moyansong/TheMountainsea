// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStates/AnimNotifyState_CheckCombo.h"
#include "Interfaces/SimpleCombatInterface.h"
#include "SimpleCombatTypes.h"

void UAnimNotifyState_CheckCombo::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ISimpleCombatInterface* MyCharacter = Cast<ISimpleCombatInterface>(MeshComp->GetOwner()))
	{
		if (FSimpleComboCheck* ComboCheck = MyCharacter->GetSimpleComboInfo(ComboName))
		{
			ComboCheck->bShortPressed = false;
			ComboCheck->UpdateComboIndex();
		}
	}
}

void UAnimNotifyState_CheckCombo::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_CheckCombo::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ISimpleCombatInterface* MyCharacter = Cast<ISimpleCombatInterface>(MeshComp->GetOwner()))
	{
		if (FSimpleComboCheck* ComboCheck = MyCharacter->GetSimpleComboInfo(ComboName))
		{
			if (ComboCheck->bShortPressed)
			{
				MyCharacter->ComboShortPressed(ComboName);
			}
			else if (ComboCheck->bLongPressed)
			{
				MyCharacter->ComboLongPressed(ComboName);
			}
		}
	}
}
