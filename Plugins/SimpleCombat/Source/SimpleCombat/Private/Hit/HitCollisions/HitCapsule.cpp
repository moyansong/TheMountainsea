// Fill out your copyright notice in the Description page of Project Settings.


#include "Hit/HitCollisions/HitCapsule.h"
#include "Components/CapsuleComponent.h"

AHitCapsule::AHitCapsule()
{
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetRootComponent());
	CapsuleCollisionComponent = Cast<UCapsuleComponent>(CollisionComponent);
}

void AHitCapsule::SetCapsuleRadius(float CapsuleRadius)
{
	if (CapsuleCollisionComponent.IsValid())
	{
		CapsuleCollisionComponent->SetCapsuleRadius(CapsuleRadius);
	}
}

void AHitCapsule::SetCapsuleHalfHeight(float CapsuleHalfHeight)
{
	if (CapsuleCollisionComponent.IsValid())
	{
		CapsuleCollisionComponent->SetCapsuleHalfHeight(CapsuleHalfHeight);
	}
}
