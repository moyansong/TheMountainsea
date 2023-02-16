// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../SimpleCombatTypes.h"
#include "AnimNotify_AnimSignal.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "AnimSignal"))
class SIMPLECOMBAT_API UAnimNotify_AnimSignal : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	UAnimNotify_AnimSignal();

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

	// 通过指定不同的AnimSignalType在同类动画通知中实现不同的逻辑
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	EAnimSignalType AnimSignalType;
};
