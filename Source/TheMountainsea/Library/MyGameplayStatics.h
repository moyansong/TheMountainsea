// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameplayStatics.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UMyGameplayStatics : public UGameplayStatics
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Character")
	static AMyCharacter* FindTargetCharacter(AMyCharacter* MyCharacter, const TArray<ECharacterType>& IgnoreTypes, float Range = 520.f);

};
