// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStates/AnimNotifyState_IgnoreInput.h"
#include "GameFramework/Character.h"

void UAnimNotifyState_IgnoreInput::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (ACharacter* MyCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if (MyCharacter->GetController() && MyCharacter->IsLocallyControlled())
		{
			if (bIgnoreAllInput)
			{
				MyCharacter->DisableInput(MyCharacter->GetWorld()->GetFirstPlayerController());
			}
			else
			{
				MyCharacter->GetController()->SetIgnoreMoveInput(bIgnoreMoveInput);
				MyCharacter->GetController()->SetIgnoreLookInput(bIgnoreLookInput);
			}
		}
	}
}

void UAnimNotifyState_IgnoreInput::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_IgnoreInput::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (ACharacter* MyCharacter = Cast<ACharacter>(MeshComp->GetOwner()))
	{
		if (MyCharacter->GetController() && MyCharacter->IsLocallyControlled())
		{
			if (bIgnoreAllInput)
			{
				MyCharacter->EnableInput(MyCharacter->GetWorld()->GetFirstPlayerController());
			}
			else
			{
				MyCharacter->GetController()->SetIgnoreMoveInput(false);
				MyCharacter->GetController()->SetIgnoreLookInput(false);
			}
		}
	}
}
