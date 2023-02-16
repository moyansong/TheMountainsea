// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitCollision.h"
#include "HitSphere.generated.h"

class USphereComponent;

/**
 * 
 */
UCLASS()
class SIMPLECOMBAT_API AHitSphere : public AHitCollision
{
	GENERATED_BODY()
	
public:
	AHitSphere();

	void SetSphereRadius(float SphereRadius);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<USphereComponent> SphereCollisionComponent;
};
