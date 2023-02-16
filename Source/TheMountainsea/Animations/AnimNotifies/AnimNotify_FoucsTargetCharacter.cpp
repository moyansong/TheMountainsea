// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_FoucsTargetCharacter.h"
#include "../../Characters/MyCharacter.h"
#include "../../Library/MyGameplayStatics.h"

void UAnimNotify_FoucsTargetCharacter::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(MeshComp->GetOwner()))
	{
		if (AMyCharacter* TargetCharacter = UMyGameplayStatics::FindTargetCharacter(MyCharacter, IgnroeCharacterTypes, Range))
		{
			FRotator FoucsRotation = FRotationMatrix::MakeFromX(TargetCharacter->GetActorLocation() - MyCharacter->GetActorLocation()).Rotator();
			MyCharacter->SetActorRotation(FoucsRotation);
		}
	}
}
