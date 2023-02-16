// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyUserWidget.h"
#include "CharacterAttributeWidget.generated.h"

class UBarText;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UCharacterAttributeWidget : public UMyUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	
};
