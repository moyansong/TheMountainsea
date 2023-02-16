// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item.h"
#include "../ItemTypes.h"
#include "Equipment.generated.h"

class AMyCharacter;

UCLASS()
class THEMOUNTAINSEA_API AEquipment : public AItem
{
	GENERATED_BODY()
	
public:
	AEquipment();
	virtual void Tick(float DeltaTime) override;
//------------------------------------------Set && Get---------------------------------------------------------
	FORCEINLINE EEquipmentType GetEquipmentType() const { return EquipmentType; }

//------------------------------------------Functions---------------------------------------------------------
	virtual void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);

	void AttachToSocket(USceneComponent* InParent, const FName& InSocketName);

protected:
	virtual void BeginPlay() override;
//------------------------------------------Parameters---------------------------------------------------------
	EEquipmentType EquipmentType = EEquipmentType::EWT_MAX;

	UPROPERTY()
	AMyCharacter* MyCharacter;

private:
//------------------------------------------Components---------------------------------------------------------

};
