// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"
#include "../../Characters/MyCharacter.h"

AEquipment::AEquipment()
{

}

void AEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
}

void AEquipment::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	SetOwner(NewOwner);
	SetInstigator(NewInstigator);
	MyCharacter = Cast<AMyCharacter>(NewOwner);
}

void AEquipment::AttachToSocket(USceneComponent* InParent, const FName& InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	this->AttachToComponent(InParent, TransformRules, InSocketName);
}