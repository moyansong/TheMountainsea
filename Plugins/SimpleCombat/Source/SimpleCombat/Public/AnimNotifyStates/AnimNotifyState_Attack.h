// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "../SimpleCombatTypes.h"
#include "AnimNotifyState_Attack.generated.h"

class AHitCollision;
class AHitBox;

/**
 * AnimNotifyState持续期间内会让碰撞体生效
 */
UCLASS(meta = (DisplayName = "Attack"))
class SIMPLECOMBAT_API UAnimNotifyState_Attack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	UAnimNotifyState_Attack();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

//------------------------------------------Functions---------------------------------------------------------




//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	TSubclassOf<AHitCollision> HitCollisionClass;

	UPROPERTY()
	AHitCollision* HitCollision;

	// 碰撞体相对位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	FVector CollisionRelativeOffsetLocation = FVector::ZeroVector;

	// 是否将HitCollision绑到角色的某个Socket上
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	bool bAttachToSocket = true;

	// 在这个Socket位置生成HitCollision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	FName SpawnSocketName = FName(TEXT("weapon_r"));

	// 绑定的Socket
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	FName AttachSocketName = FName(TEXT("weapon_r"));

	// 打击的类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	EHitType HitType = EHitType::EHT_SlightHit;

	// 为true则只伤害打到的第一个目标，否则伤害打到的全部目标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	bool bSingleTarget = false;

	// SendGameplayEventToActor(Buff)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	TArray<FName> Buffs;

	UPROPERTY(BlueprintReadOnly)
	bool bHitBox = true;

	UPROPERTY(BlueprintReadOnly)
	bool bHitSphere = false;

	UPROPERTY(BlueprintReadOnly)
	bool bHitCustom = false;

	UPROPERTY(BlueprintReadOnly)
	bool bHitCapsule = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitBox"))
	FVector BoxExtent = FVector(32.f, 32.f, 32.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitSphere"))
	float SphereRadius = 32.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitCapsule"))
	float CapsuleRadius = 22.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitCapsule"))
	float CapsuleHalfHeight = 44.f;
};
