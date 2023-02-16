// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "../SimpleCombatTypes.h"
#include "AnimNotify_Attack.generated.h"

class AHitCollision;
class AHitBox;

/**
 * 
 */
UCLASS(meta = (DisplayName = "Attack"))
class SIMPLECOMBAT_API UAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()

public:
	UAnimNotify_Attack();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

//------------------------------------------Functions---------------------------------------------------------




//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	TSubclassOf<AHitCollision> HitCollisionClass;

	// 碰撞体存活时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	float HitCollisionLifeTime = 4.f;;

	// 碰撞体相对于根组件的位置
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
	FVector BoxExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitSphere"))
	float SphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitCapsule"))
	float CapsuleHalfHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter, meta = (EditCondition = "bHitCapsule"))
	float CapsuleRadius;
};
