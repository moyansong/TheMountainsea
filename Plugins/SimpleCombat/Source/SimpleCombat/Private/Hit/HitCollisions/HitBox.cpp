// Fill out your copyright notice in the Description page of Project Settings.


#include "Hit/HitCollisions/HitBox.h"
#include "Components/BoxComponent.h"

AHitBox::AHitBox()
{
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(GetRootComponent());
	BoxCollisionComponent = Cast<UBoxComponent>(CollisionComponent);
}

void AHitBox::SetBoxExtent(FVector BoxExtent)
{
	if (BoxCollisionComponent.IsValid())
	{
		BoxCollisionComponent->SetBoxExtent(BoxExtent);
	}
}
