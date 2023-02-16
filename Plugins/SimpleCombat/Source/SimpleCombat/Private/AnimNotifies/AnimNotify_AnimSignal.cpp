// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_AnimSignal.h"
#include "Interfaces/SimpleCombatInterface.h"

UAnimNotify_AnimSignal::UAnimNotify_AnimSignal()
{
}

FString UAnimNotify_AnimSignal::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_AnimSignal::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (ISimpleCombatInterface* SimpleCombatInterface = Cast<ISimpleCombatInterface>(MeshComp->GetOwner()))
	{
		SimpleCombatInterface->AnimSignal(AnimSignalType);
	}
}
