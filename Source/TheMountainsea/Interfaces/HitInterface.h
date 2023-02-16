// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "../TheMountainseaTypes.h"
#include "HitInterface.generated.h"

class AWeapon;

UINTERFACE(MinimalAPI)
class UHitInterface : public UInterface
{
	GENERATED_BODY()
};

class THEMOUNTAINSEA_API IHitInterface
{
	GENERATED_BODY()

public:
	virtual void GetHit(const FHitData& HitData) = 0;
};
