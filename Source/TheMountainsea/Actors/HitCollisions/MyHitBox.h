// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hit/HitCollisions/HitBox.h"
#include "MyHitBox.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API AMyHitBox : public AHitBox
{
	GENERATED_BODY()
	
public:
	AMyHitBox();


protected:

	virtual void OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnCollisionComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
