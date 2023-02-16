// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Main/GameMainWidget.h"
#include "../TheMountainsea.h"

AMyHUD::AMyHUD()
{
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	GameMainWidget = CreateAndShowWidget<UGameMainWidget>(GameMainWidgetClass);
	
}

void AMyHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
