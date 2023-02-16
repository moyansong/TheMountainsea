// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../../Characters/CharacterTypes.h"
#include "AnimNotify_FoucsTargetCharacter.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "FoucsTargetCharacter"))
class THEMOUNTAINSEA_API UAnimNotify_FoucsTargetCharacter : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	UPROPERTY(EditDefaultsOnly, Category = Paramerter)
	TArray<ECharacterType> IgnroeCharacterTypes;

	UPROPERTY(EditDefaultsOnly, Category = Paramerter)
	float Range = 520.f;
};
