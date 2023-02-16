// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActorComponent.h"
#include "../Items/ItemTypes.h"
#include "EquipmentComponent.generated.h"

class AItem;
class AWeapon;
class AEquipment;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEMOUNTAINSEA_API UEquipmentComponent : public UMyActorComponent
{
	GENERATED_BODY()

public:	
	friend class AMyCharacter;
	friend class APlayerCharacter;

	UEquipmentComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//------------------------------------------Set && Get---------------------------------------------------------
	void SetWeaponCollision(bool bCanWeaponHit);

//------------------------------------------Functions---------------------------------------------------------
	void SpawnDefaultEquipments();

protected:
	virtual void BeginPlay() override;

//------------------------------------------Parameters---------------------------------------------------------

private:

//------------------------------------------Equipments---------------------------------------------------------
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TMap<EEquipmentType, TSubclassOf<AEquipment>> EquipmentClasses;
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	TMap<EEquipmentType, AEquipment*> Equipments;

	UPROPERTY(EditAnywhere, Category = Equipment)
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY(VisibleAnywhere, Category = Equipment)
	AWeapon* Weapon;
		
};
