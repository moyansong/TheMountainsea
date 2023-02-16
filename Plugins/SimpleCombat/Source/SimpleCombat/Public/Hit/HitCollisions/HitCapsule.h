// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitCollision.h"
#include "HitCapsule.generated.h"

class UCapsuleComponent;

/**
 * 
 */
UCLASS()
class SIMPLECOMBAT_API AHitCapsule : public AHitCollision
{
	GENERATED_BODY()
	
public:
	AHitCapsule();

	void SetCapsuleRadius(float CapsuleRadius);

	void SetCapsuleHalfHeight(float CapsuleHalfHeight);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UCapsuleComponent> CapsuleCollisionComponent;
};
