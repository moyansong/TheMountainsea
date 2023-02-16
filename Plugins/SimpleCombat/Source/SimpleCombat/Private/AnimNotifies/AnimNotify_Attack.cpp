// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AnimNotify_Attack.h"
#include "Interfaces/SimpleCombatInterface.h"
#include "Components/ShapeComponent.h"
#include "Hit/HitCollisions/HitBox.h"
#include "Hit/HitCollisions/HitCustom.h"
#include "Hit/HitCollisions/HitSphere.h"
#include "Hit/HitCollisions/HitCapsule.h"
#include "GameFramework/Character.h"

UAnimNotify_Attack::UAnimNotify_Attack()
{
	NotifyColor = FColor::Red;
	HitCollisionClass = AHitBox::StaticClass();
}

void UAnimNotify_Attack::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetPropertyName().ToString() == TEXT("HitCollisionClass"))
	{
		if (HitCollisionClass.GetDefaultObject()->IsA(AHitBox::StaticClass()))
		{
			bHitBox = true;
			bHitCapsule = false;
			bHitCustom = false;
			bHitSphere = false;
		}
		else if (HitCollisionClass.GetDefaultObject()->IsA(AHitCapsule::StaticClass()))
		{
			bHitCapsule = true;
			bHitBox = false;
			bHitCustom = false;
			bHitSphere = false;
		}
		else if (HitCollisionClass.GetDefaultObject()->IsA(AHitCustom::StaticClass()))
		{
			bHitCustom = true;
			bHitBox = false;
			bHitCapsule = false;
			bHitSphere = false;
		}
		else if (HitCollisionClass.GetDefaultObject()->IsA(AHitSphere::StaticClass()))
		{
			bHitSphere = true;
			bHitBox = false;
			bHitCapsule = false;
			bHitCustom = false;
		}
	}
}

FString UAnimNotify_Attack::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}

void UAnimNotify_Attack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AActor* Owner = MeshComp ? MeshComp->GetOwner() : nullptr;// 转为ACharacter，Spawn的Actior无法在动画编辑器里显示?
	if (Owner && Owner->HasAuthority() && HitCollisionClass)
	{
		UWorld* World = Owner->GetWorld();
		if (World)
		{
			FVector SpawnLocation = MeshComp->GetSocketLocation(SpawnSocketName);
			FRotator SpawnRotation = MeshComp->GetSocketRotation(SpawnSocketName);
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = Owner;
			SpawnParameters.Instigator = Cast<APawn>(Owner);

			AHitCollision* HitCollision = World->SpawnActor<AHitCollision>(
				HitCollisionClass,
				SpawnLocation,
				SpawnRotation,
				SpawnParameters
			);

			if (HitCollision)
			{
				HitCollision->SetHitType(HitType);
				HitCollision->SetBuffs(Buffs);
				HitCollision->SetLifeSpan(HitCollisionLifeTime);

				FVector CollisionRelativeLocation = HitCollision->GetCollisionComponent() ? HitCollision->GetCollisionComponent()->GetRelativeLocation() : FVector::ZeroVector;
				HitCollision->SetCollisionRelativePosition(CollisionRelativeLocation + CollisionRelativeOffsetLocation);

				if (bAttachToSocket)
				{
					HitCollision->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, AttachSocketName);
				}

				if (AHitBox* HitBox = Cast<AHitBox>(HitCollision))
				{
					HitBox->SetBoxExtent(BoxExtent);
				}
				else if (AHitCapsule* HitCapsule = Cast<AHitCapsule>(HitCollision))
				{
					HitCapsule->SetCapsuleRadius(CapsuleRadius);
					HitCapsule->SetCapsuleHalfHeight(CapsuleHalfHeight);
				}
				else if (AHitSphere* HitSphere = Cast<AHitSphere>(HitCollision))
				{
					HitSphere->SetSphereRadius(SphereRadius);
				}
				else if (AHitCustom* HitCustom = Cast<AHitCustom>(HitCollision))
				{

				}

				//HitCollision->SetCollisionEnabled(true);
			}
		}
	}
}
