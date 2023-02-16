// Fill out your copyright notice in the Description page of Project Settings.


#include "Hit/HitCollisions/HitSphere.h"
#include "Components/SphereComponent.h"

AHitSphere::AHitSphere()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetRootComponent());
	SphereCollisionComponent = Cast<USphereComponent>(CollisionComponent);
}

void AHitSphere::SetSphereRadius(float SphereRadius)
{
	if (SphereCollisionComponent.IsValid())
	{
		SphereCollisionComponent->SetSphereRadius(SphereRadius);
	}
}
