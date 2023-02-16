// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Base.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../AIControllers/MyAIController.h"
#include "../../Characters/AICharacters/AICharacter.h"

void UBTService_Base::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		BBKey_Target.ResolveSelectedKey(*BBAsset);
		BBKey_IsAlive.ResolveSelectedKey(*BBAsset);
		BBKey_TargetDistance.ResolveSelectedKey(*BBAsset);
		BBKey_TargetLocation.ResolveSelectedKey(*BBAsset);
	}
}

bool UBTService_Base::CheckKeyType() const
{
	return  BBKey_IsAlive.SelectedKeyType == UBlackboardKeyType_Bool::StaticClass() &&
		BBKey_Target.SelectedKeyType == UBlackboardKeyType_Object::StaticClass() &&
		BBKey_TargetDistance.SelectedKeyType == UBlackboardKeyType_Float::StaticClass() &&
		BBKey_TargetLocation.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass();
}

void UBTService_Base::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!CheckKeyType()) return;

	if (AMyAIController* MyController = Cast<AMyAIController>(OwnerComp.GetOwner()))
	{
		if (AAICharacter* MyCharacter = Cast<AAICharacter>(MyController->GetPawn()))
		{
			if (UBlackboardComponent* MyBlackboard = OwnerComp.GetBlackboardComponent())
			{
				MyBlackboard->SetValueAsBool(BBKey_IsAlive.SelectedKeyName, MyCharacter->IsAlive());
				if (MyCharacter->IsAlive())
				{
					AMyCharacter* Target = Cast<AMyCharacter>(MyBlackboard->GetValueAsObject(BBKey_Target.SelectedKeyName));
					if (Target)
					{
						const float Distance = FVector::Distance(MyCharacter->GetActorLocation(), Target->GetActorLocation());

						MyBlackboard->SetValueAsFloat(BBKey_TargetDistance.SelectedKeyName, Distance);
						MyBlackboard->SetValueAsVector(BBKey_TargetLocation.SelectedKeyName, Target->GetActorLocation());
					}
					else
					{
						MyBlackboard->SetValueAsFloat(BBKey_TargetDistance.SelectedKeyName, 9999999.f);
						MyBlackboard->SetValueAsVector(BBKey_TargetLocation.SelectedKeyName, MyCharacter->GetActorLocation());
					}
				}
				else
				{
					MyBlackboard->SetValueAsVector(BBKey_TargetLocation.SelectedKeyName, MyCharacter->GetActorLocation());
				}
			}
		}
	}
}

