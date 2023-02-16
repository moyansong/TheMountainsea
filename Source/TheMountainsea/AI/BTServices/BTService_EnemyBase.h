// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTService_Base.h"
#include "BTService_EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UBTService_EnemyBase : public UBTService_Base
{
	GENERATED_BODY()
	
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector BBKey_CanAttack;

protected:
	virtual bool CheckKeyType() const;
};
