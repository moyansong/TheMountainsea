// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Equipments/Equipment.h"
#include "../ItemTypes.h"
#include "Weapon.generated.h"

class UBoxComponent;
class AMyCharacter;
class UFieldSystemComponent;
class URadialVector;
class URadialFalloff;
class UFieldSystemMetaDataFilter;

USTRUCT(BlueprintType)
struct FBoxInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;

	UPROPERTY()
	FVector BoxExtent;
};

// 记录一帧里武器所有HitBox的信息
USTRUCT(BlueprintType)
struct FFramePackage
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FBoxInformation> HitBoxInfo;

};

UCLASS()
class THEMOUNTAINSEA_API AWeapon : public AEquipment
{
	GENERATED_BODY()

public:
	AWeapon();
	virtual void Tick(float DeltaTime) override;
//-----------------------------------------Set && Get---------------------------------------------------------
	void SetCanHit(bool bCanWeaponHit);
	
	FORCEINLINE EWeaponType GetWeaponType() const { return WeaponType; }
//-----------------------------------------Functions---------------------------------------------------------
	void Test();

	virtual void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator) override;

	// 要打碎物体时调用
	void CreateFields(const FVector& FieldLocation);

protected:
	virtual void BeginPlay() override;

	void SaveFramePackage();

	void TraceHit();

	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

//-----------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(EditAnywhere, Category = WeaponType)
	EWeaponType WeaponType = EWeaponType::EWT_MAX;

	bool bCanHit = false;

	TArray<AActor*> HitIgnoreActors;

private:
	FFramePackage PrevFramePackage;
	FFramePackage CurrFramePackage;
//-----------------------------------------Components---------------------------------------------------------
	TArray<UBoxComponent*> HitBoxs;
	
	UPROPERTY(VisibleAnywhere, Category = Component)
	UBoxComponent* HitBox1;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UFieldSystemComponent* FieldSystem;

	UPROPERTY(VisibleAnywhere, Category = Component)
	URadialVector* RadialVector;

	UPROPERTY(VisibleAnywhere, Category = Component)
	URadialFalloff* RadialFalloff;

	UPROPERTY(VisibleAnywhere, Category = Component)
	UFieldSystemMetaDataFilter* FieldSystemMetaDataFilter;
};
