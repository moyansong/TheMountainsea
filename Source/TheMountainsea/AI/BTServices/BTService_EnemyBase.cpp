// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_EnemyBase.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AIControllers/MyAIController.h"
#include "../../Characters/AICharacters/Enemies/Enemy.h"

void UBTService_EnemyBase::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		BBKey_CanAttack.ResolveSelectedKey(*BBAsset);
	}
}

void UBTService_EnemyBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!CheckKeyType()) return;

	if (AMyAIController* MyController = Cast<AMyAIController>(OwnerComp.GetOwner()))
	{
		if (AEnemy* MyCharacter = Cast<AEnemy>(MyController->GetPawn()))
		{
			if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
			{
				AMyCharacter* Target = Cast<AMyCharacter>(MyBlackboard->GetValueAsObject(BBKey_Target.SelectedKeyName));

				const float Distance = MyBlackboard->GetValueAsFloat(BBKey_TargetDistance.SelectedKeyName);
				MyBlackboard->SetValueAsBool(BBKey_CanAttack.SelectedKeyName, Target && Distance <= MyCharacter->GetAttackRange());
				
			}
		}
	}
}

bool UBTService_EnemyBase::CheckKeyType() const
{
	return Super::CheckKeyType() &&
		BBKey_CanAttack.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass();
}
