#pragma once

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	EET_Weapon UMETA(DisplayName = "Weapon"),
	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EWT_Sword UMETA(DisplayName = "Sword"),
	EWT_Stick UMETA(DisplayName = "Stick"),
	EWT_MAX UMETA(DisplayName = "DefaultMAX")
};