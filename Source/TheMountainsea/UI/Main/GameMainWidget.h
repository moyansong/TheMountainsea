// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyUserWidget.h"
#include "GameMainWidget.generated.h"

class UPlayerAttributeWidget;

/**
 * 游戏中展示的所有Widget的集合
 */
UCLASS()
class THEMOUNTAINSEA_API UGameMainWidget : public UMyUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(meta = (BindWidget))
	UPlayerAttributeWidget* PlayerAttributeWidget;
};
