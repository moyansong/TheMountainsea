// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Base.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UBTService_Base : public UBTService
{
	GENERATED_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	// 自己是否死亡
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBKey_IsAlive;

	// 目标
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBKey_Target;

	// 目标距离
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBKey_TargetDistance;

	// 要移动到的位置，没死的话是目标点，死了是自己的位置
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBKey_TargetLocation;

protected:
	virtual bool CheckKeyType() const;
};
