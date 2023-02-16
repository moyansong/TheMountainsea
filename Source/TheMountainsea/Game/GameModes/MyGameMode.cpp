// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"
#include "../GameStates/MyGameState.h"

AMyGameMode::AMyGameMode()
{
}

void AMyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	
}
