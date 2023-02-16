// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_Cooldown.h"
#include "BTDecorator_EnemyCooldown.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UBTDecorator_EnemyCooldown : public UBTDecorator_Cooldown
{
	GENERATED_BODY()

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
