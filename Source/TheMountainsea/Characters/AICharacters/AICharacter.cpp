// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "../../AI/AIControllers/MyAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AAICharacter::AAICharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// 不开这个，行为树里的RotatetofaceBBentry用不了
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MyController = Cast<AMyAIController>(GetController());
}

void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return 0.0f;
}

void AAICharacter::GetHit(const FHitData& HitData)
{
	Super::GetHit(HitData);

}

void AAICharacter::Die()
{
	Super::Die();

}
