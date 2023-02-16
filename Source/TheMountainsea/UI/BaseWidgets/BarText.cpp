// Fill out your copyright notice in the Description page of Project Settings.


#include "BarText.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Overlay.h"

void UBarText::SetPercent(float InPercent)
{
	if (ProgressBar)
	{
		ProgressBar->SetPercent(InPercent);
	}
}

void UBarText::SetText(FText InText)
{
	if (TextBlock)
	{
		TextBlock->SetText(InText);
	}
}

void UBarText::SetValue(float Value, float MaxValue)
{
	SetPercent(Value / MaxValue);
	SetText(FText::FromString(FString::Printf(TEXT("%d / %d"), FMath::CeilToInt(Value), FMath::CeilToInt(MaxValue))));
}

