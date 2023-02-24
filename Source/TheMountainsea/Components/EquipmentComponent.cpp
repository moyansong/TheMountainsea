// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "../Characters/MyCharacter.h"
#include "../Items/Weapons/Weapon.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEquipmentComponent::SetWeaponCollision(bool bCanWeaponHit)
{
	if (Weapon)
	{
		Weapon->SetCanHit(bCanWeaponHit);
	}
}

void UEquipmentComponent::SpawnDefaultEquipments()
{
	if (!MyCharacter.IsValid()) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	APawn* InstigatorPawn = Cast<APawn>(MyCharacter);
	SpawnParams.Instigator = InstigatorPawn;

	if (WeaponClass)
	{
		Weapon = GetWorld()->SpawnActor<AWeapon>(
			WeaponClass,
			FVector(0.f, 0.f, 10000.f),
			FRotator::ZeroRotator,
			SpawnParams
		);
		if (Weapon)
		{
			Weapon->Equip(MyCharacter->GetMesh(), FName("weapon_r"), GetOwner(), InstigatorPawn);
			if (!EquipmentClasses.Contains(Weapon->GetEquipmentType())) EquipmentClasses.Emplace(Weapon->GetEquipmentType(), WeaponClass);
			if (!Equipments.Contains(Weapon->GetEquipmentType())) Equipments.Emplace(Weapon->GetEquipmentType(), Weapon);
		}
	}
}
