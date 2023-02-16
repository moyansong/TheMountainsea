// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../AICharacters/AICharacter.h"
#include "Enemy.generated.h"

UCLASS()
class THEMOUNTAINSEA_API AEnemy : public AAICharacter
{
	GENERATED_BODY()
	
public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

//------------------------------------------Set && Get---------------------------------------------------------

	FORCEINLINE float GetAttackRange() const { return AttackRange; }

//------------------------------------------Functions---------------------------------------------------------
	virtual void GetHit(const FHitData& HitData) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Die() override;

protected:
	virtual void BeginPlay() override;
//------------------------------------------Paramters---------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = Parameter)
	float AttackRange = 300.f;

private:

};
