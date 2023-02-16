// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_AttackTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AIControllers/MyAIController.h"

void UBTTaskNode_AttackTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		BBKey_SkillName.ResolveSelectedKey(*BBAsset);
	}
}

EBTNodeResult::Type UBTTaskNode_AttackTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
	{
		if (AMyAIController* MyController = Cast<AMyAIController>(OwnerComp.GetOwner()))
		{
			//const FName SkillName = MyBlackboard->GetValueAsName(BBKey_SkillName.SelectedKeyName);
			MyController->Attack(TEXT("NormalAttack"));
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}

