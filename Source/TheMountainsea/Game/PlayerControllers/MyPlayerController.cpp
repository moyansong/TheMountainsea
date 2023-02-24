// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "../../UI/MyHUD.h"
#include "../../TheMountainsea.h"
#include "../../Abilities/MyAbilitySystemComponent.h"
#include "../../Characters/PlayerCharacters/PlayerCharacter.h"

AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = GetHUD<AMyHUD>();
}

void AMyPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	MyPlayerCharacter = Cast<APlayerCharacter>(P);
}

void AMyPlayerController::AcknowledgePossession(APlayerCharacter* NewCharacter)
{
	MyPlayerCharacter = NewCharacter;
}