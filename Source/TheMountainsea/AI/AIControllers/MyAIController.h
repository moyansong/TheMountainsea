// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UBehaviorTree;
class AMyCharacter;
class AAICharacter;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
public:

//------------------------------------------Set && Get---------------------------------------------------------
	void SetTarget(AMyCharacter* Target);
	FORCEINLINE AMyCharacter* GetTarget() const { return TargetCharacter.Get(); }

//------------------------------------------Functions---------------------------------------------------------
	virtual void Attack(const FName& SkillName = TEXT("NormalAttack"));

protected:
	virtual void BeginPlay() override;

//------------------------------------------Parameters---------------------------------------------------------

	UPROPERTY(EditDefaultsOnly, Category = AI)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(VisibleANywhere, Category = Parameter)
	TWeakObjectPtr<AMyCharacter> TargetCharacter;

	UPROPERTY(VisibleANywhere, Category = Parameter)
	TWeakObjectPtr<AAICharacter> MyAICharacter;
};
