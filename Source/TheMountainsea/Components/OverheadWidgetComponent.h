// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "OverheadWidgetComponent.generated.h"

class UOverheadWidget;

/**
 *显示在人物头顶的WidgetComponent 
 */
UCLASS()
class THEMOUNTAINSEA_API UOverheadWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	friend class AMyCharacter;

//------------------------------------------Functions---------------------------------------------------------
	


protected:

//------------------------------------------Parameters---------------------------------------------------------

private:
	UPROPERTY()
	AMyCharacter* MyCharacter;

	UPROPERTY()
	UOverheadWidget* OverheadWidget;
};
