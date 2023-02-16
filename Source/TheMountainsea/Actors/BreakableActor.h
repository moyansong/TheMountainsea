// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;
class UCapsuleComponent;

UCLASS()
class THEMOUNTAINSEA_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	ABreakableActor();
	virtual void Tick(float DeltaTime) override;

//-----------------------------------------Functions---------------------------------------------------------
	virtual void GetHit(const FHitData& HitData) override;

protected:
	virtual void BeginPlay() override;

	void BreakingEffect(const FHitResult& HitResult);

//-----------------------------------------Parameters---------------------------------------------------------
	bool bBroken = false;

private:
	UPROPERTY(EditAnywhere, Category = Effect)
	USoundBase* BreakingSound;

	UPROPERTY(EditAnywhere, Category = Effect)
	UParticleSystem* BreakingParticle;
//-----------------------------------------Components---------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = Component)
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UCapsuleComponent* CapsuleComponent;
};
