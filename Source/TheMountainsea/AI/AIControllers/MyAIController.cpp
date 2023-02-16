// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Characters/AICharacters/AICharacter.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	RunBehaviorTree(BehaviorTree);
}

void AMyAIController::SetTarget(AMyCharacter* Target)
{
	TargetCharacter = Target;
	if (GetBlackboardComponent())
	{
		GetBlackboardComponent()->SetValueAsObject("Target", Target);
	}
}

void AMyAIController::Attack(const FName& SkillName)
{
	if (!MyAICharacter.IsValid()) MyAICharacter = Cast<AAICharacter>(GetPawn());
	if (MyAICharacter.IsValid())
	{
		MyAICharacter->ActivateSkill(SkillName);
	}
}
