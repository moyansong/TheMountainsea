// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fonts/SlateFontInfo.h"
#include "Styling/SlateColor.h"
#include "Styling/SlateTypes.h"
#include "../MyUserWidget.h"
#include "BarText.generated.h"

class UProgressBar;
class UTextBlock;
class UOverlay;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UBarText : public UMyUserWidget
{
	GENERATED_BODY()
	
public:

//---------------------------------------Functions---------------------------------------------------------------------
	// 将Bar的Percent设为Value / MaxValue， 将Text设为"Value / MaxValue"
	void SetValue(float Value, float MaxValue);

	void SetText(FText InText);
	void SetPercent(float InPercent);

//---------------------------------------Parameters---------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TextBlock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameter, meta = (MultiLine = "true"))
	FText Text = FText::FromString(TEXT("Value / MaxValue"));

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameter)
	FSlateFontInfo TextFont;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameter)
	FSlateColor TextColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameter)
	FLinearColor BarColorAndOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Parameter, meta = (UIMin = "0", UIMax = "1"))
	float BarPercent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parameter)
	FProgressBarStyle BarStyle;
};
