// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyStates/AnimNotifyState_Attack.h"
#include "Interfaces/SimpleCombatInterface.h"
#include "Components/ShapeComponent.h"
#include "Hit/HitCollisions/HitBox.h"
#include "Hit/HitCollisions/HitCustom.h"
#include "Hit/HitCollisions/HitSphere.h"
#include "Hit/HitCollisions/HitCapsule.h"
#include "GameFramework/Character.h"

UAnimNotifyState_Attack::UAnimNotifyState_Attack()
{
	NotifyColor = FColor::Red;
	HitCollisionClass = AHitBox::StaticClass();
}

#if WITH_EDITOR
void UAnimNotifyState_Attack::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
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
#endif

void UAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

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

			HitCollision = World->SpawnActor<AHitCollision>(
				HitCollisionClass,
				SpawnLocation,
				SpawnRotation,
				SpawnParameters
			);

			if (HitCollision)
			{
				HitCollision->SetHitType(HitType);
				HitCollision->SetBuffs(Buffs);
					
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

void UAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (HitCollision)
	{
		HitCollision->Destroy();
	}
}
