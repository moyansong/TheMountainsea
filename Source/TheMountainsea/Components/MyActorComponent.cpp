// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"
#include "../Characters/MyCharacter.h"

UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!MyCharacter.IsValid()) MyCharacter = Cast<AMyCharacter>(GetOwner());
}

bool UMyActorComponent::HasAuthority() const
{
	return MyCharacter.IsValid() && MyCharacter->HasAuthority();
}

bool UMyActorComponent::IsLocallyControlled() const
{
	return MyCharacter.IsValid() && MyCharacter->IsLocallyControlled();
}
