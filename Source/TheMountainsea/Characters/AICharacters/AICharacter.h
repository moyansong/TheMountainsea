// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyCharacter.h"
#include "AICharacter.generated.h"

class AMyAIController;

UCLASS()
class THEMOUNTAINSEA_API AAICharacter : public AMyCharacter
{
	GENERATED_BODY()
	
public:
	AAICharacter();
	virtual void Tick(float DeltaTime) override;

//------------------------------------------Set && Get---------------------------------------------------------
	

//------------------------------------------Functions---------------------------------------------------------
	virtual void GetHit(const FHitData& HitData) override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Die() override;

protected:
	virtual void BeginPlay() override;

//------------------------------------------Paramters---------------------------------------------------------

	UPROPERTY()
	TWeakObjectPtr<AMyAIController> MyController;

private:

};
