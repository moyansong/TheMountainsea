// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHitBox.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags.h"
#include "../../TheMountainsea.h"
#include "../../Interfaces/HitInterface.h"
#include "../../Characters/MyCharacter.h"

AMyHitBox::AMyHitBox()
{

}

void AMyHitBox::OnCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionComponentBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	if (GetOwner() == OtherActor) return;

	APawn* InstigatorPawn = GetInstigator() ? GetInstigator() : Cast<APawn>(GetOwner());
	AMyCharacter* MyCharacter = Cast<AMyCharacter>(InstigatorPawn);

	FGameplayEventData EventData;
	EventData.Instigator = InstigatorPawn;
	EventData.Target = OtherActor;

	if (IHitInterface* HitTarget = Cast<IHitInterface>(OtherActor))
	{
		FHitData HitData;
		HitData.EventData = EventData;
		HitData.HitType = HitType;
		HitData.HitCauser = this;
		HitData.InstigatorCharacter = MyCharacter;

		HitTarget->GetHit(HitData);
	}

	if (MyCharacter)
	{
		// Apply GE
		for (auto& Buff : Buffs)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
				GetOwner(),
				MyCharacter->GetSkillTag(Buff),
				EventData
			);
		}
	}
}

void AMyHitBox::OnCollisionComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionComponentEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
