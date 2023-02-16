// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Components/CapsuleComponent.h"
#include "../TheMountainsea.h"
#include "../Items/Weapons/Weapon.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
	GeometryCollection->SetSimulatePhysics(false);
	GeometryCollection->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	// GeometryCollection无法被BoxTrace？
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GeometryCollection->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetupAttachment(GetRootComponent());
	CapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	// 暂时用CapsuleComponent代替GeometryCollection去检测Hit
	CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	CapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ABreakableActor::GetHit(const FHitData& HitData)
{
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//void ABreakableActor::GetHit(const FHitResult& HitResult, AActor* Hitter, AWeapon* HitWeapon)
//{
//	if (bBroken) return;
//
//	bBroken = true;
//	BreakingEffect(HitResult);
//	GeometryCollection->SetSimulatePhysics(true);
//	HitWeapon->CreateFields(HitResult.ImpactPoint);
//	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//}

void ABreakableActor::BreakingEffect(const FHitResult& HitResult)
{
	if (BreakingSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			BreakingSound,
			HitResult.ImpactPoint
		);
	}
	if (BreakingParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			BreakingParticle,
			HitResult.ImpactPoint
		);
	}
}
