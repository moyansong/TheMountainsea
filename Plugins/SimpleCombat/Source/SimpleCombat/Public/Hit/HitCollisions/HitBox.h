// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitCollision.h"
#include "HitBox.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class SIMPLECOMBAT_API AHitBox : public AHitCollision
{
	GENERATED_BODY()

public:
	AHitBox();

	void SetBoxExtent(FVector BoxExtent);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Component, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UBoxComponent> BoxCollisionComponent;
};
