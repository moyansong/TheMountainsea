// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "../../../AI/AIControllers/MyAIController.h"

AEnemy::AEnemy()
{
	CharacterType = ECharacterType::ECT_Enemy;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	SetOverheadWidgetVisibility(false);
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return 0.0f;
}

void AEnemy::GetHit(const FHitData& HitData)
{
	Super::GetHit(HitData);

	SetOverheadWidgetVisibility(true);
	if (MyController.IsValid())
	{
		MyController->SetTarget(HitData.InstigatorCharacter.Get());
	}
}

void AEnemy::Die()
{
	Super::Die();

	SetLifeSpan(5.f);
}
