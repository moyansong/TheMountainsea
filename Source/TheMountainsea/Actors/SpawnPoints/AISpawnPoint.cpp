// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"
#include "../../Characters/AICharacters/AICharacter.h"

AAISpawnPoint::AAISpawnPoint()
{
}

void AAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();
}

void AAISpawnPoint::SpawnAICharacter(int32 CharacterID, int32 Level)
{
	if (GetWorld() && GetWorld()->IsServer())
	{

	}
}
