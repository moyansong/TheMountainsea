// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_IgnoreInput.generated.h"

/**
 * NotifyBegin开始时屏蔽部分输入，NotifyEnd解除屏蔽
 */
UCLASS(meta = (DisplayName = "IgnoreInput"))
class SIMPLECOMBAT_API UAnimNotifyState_IgnoreInput : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool bIgnoreAllInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool bIgnoreMoveInput = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	bool bIgnoreLookInput = false;
};
