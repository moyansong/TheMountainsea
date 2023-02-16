// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameplayStatics.h"
#include "EngineUtils.h"
#include "../Characters/MyCharacter.h"

AMyCharacter* UMyGameplayStatics::FindTargetCharacter(AMyCharacter* MyCharacter, const TArray<ECharacterType>& IgnoreTypes, float Range)
{
	if (!MyCharacter || !MyCharacter->GetWorld()) return nullptr;

	UWorld* World = MyCharacter->GetWorld();
	for (TActorIterator<AMyCharacter> It(World, AMyCharacter::StaticClass()); It; ++It)
	{
		if (AMyCharacter* TargetCharacter = *It)
		{
			if (TargetCharacter != MyCharacter && !IgnoreTypes.Find(TargetCharacter->GetCharacterType()))
			{
				if (FVector::Distance(TargetCharacter->GetActorLocation(), MyCharacter->GetActorLocation()) < Range)
				{
					return TargetCharacter;
				}
			}
		}
	}
	return nullptr;
}
