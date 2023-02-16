// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "../../UI/MyHUD.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Init();
}

void AMyPlayerController::Init()
{
	if (!MyPlayerCharacter.IsValid())
	{
		MyPlayerCharacter = GetPawn<APlayerCharacter>();
	}
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = GetHUD<AMyHUD>();
}
