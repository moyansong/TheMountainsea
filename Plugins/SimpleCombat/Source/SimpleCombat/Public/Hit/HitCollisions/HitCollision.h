// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../SimpleCombatTypes.h"
#include "HitCollision.generated.h"

class UShapeComponent;

UCLASS()
class SIMPLECOMBAT_API AHitCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	AHitCollision();
	virtual void Tick(float DeltaTime) override;

//------------------------------------------Set && Get---------------------------------------------------------
	FORCEINLINE UShapeComponent* GetCollisionComponent() const { return CollisionComponent; }
	
	void SetCollisionRelativePosition(FVector NewLocation);

	void SetCollisionEnabled(bool CollisionEnabled);

	FORCEINLINE EHitType GetHitType() const { return HitType; }
	FORCEINLINE void SetHitType(EHitType Type) { HitType = Type; }

	FORCEINLINE void SetBuffs(const TArray<FName>& InBuffs) { Buffs = InBuffs; }

//------------------------------------------Functions---------------------------------------------------------

protected:
	UFUNCTION()
	virtual void OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnCollisionComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void BeginPlay() override;

//------------------------------------------Parameters---------------------------------------------------------
	// 子类里创建
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UShapeComponent> CollisionComponent;

	// 打击的类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	EHitType HitType = EHitType::EHT_SlightHit;

	bool bCollisionEnabled = false;

	UPROPERTY()
	TArray<FName> Buffs;

private:

};
