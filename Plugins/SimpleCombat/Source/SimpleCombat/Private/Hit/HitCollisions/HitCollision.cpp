// Fill out your copyright notice in the Description page of Project Settings.


#include "Hit/HitCollisions/HitCollision.h"
#include "Components/ShapeComponent.h"

AHitCollision::AHitCollision()
{
	PrimaryActorTick.bCanEverTick = true;

	// 只有蓝图会自动创建根组件
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

void AHitCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitCollision::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionComponent)
	{
		//SetCollisionEnabled(false);
		CollisionComponent->SetHiddenInGame(false);
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHitCollision::OnCollisionComponentBeginOverlap);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AHitCollision::OnCollisionComponentEndOverlap);
	}
}

void AHitCollision::SetCollisionRelativePosition(FVector NewLocation)
{
	if (CollisionComponent)
	{
		CollisionComponent->SetRelativeLocation(NewLocation);
	}
}

void AHitCollision::SetCollisionEnabled(bool CollisionEnabled)
{
	bCollisionEnabled = CollisionEnabled;
	if (CollisionComponent)
	{
		if (bCollisionEnabled)
		{
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		else
		{
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
}

void AHitCollision::OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AHitCollision::OnCollisionComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}