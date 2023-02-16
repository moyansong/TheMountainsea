#pragma once

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	ECT_NONE		UMETA(DisplayName = "None"),
	ECT_Player		UMETA(DisplayName = "Player"),	// ID : 1 ～ 99
	ECT_Enemy		UMETA(DisplayName = "Enemy"),	// ID : 100 ～ 499
	ECT_Boss		UMETA(DisplayName = "Boss"),	// ID : 500 ～ 799
	ECT_NPC			UMETA(DisplayName = "NPC"),		// ID : 800 ～ 999
	ECT_Max			UMETA(DisplayName = "DefaultMax"),
};

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_OutCombat UMETA(DisplayName = "OutCombat"), // 脱战
	ECS_InCombat UMETA(DisplayName = "InCombat"),	// 战斗中
	ECS_Attacking UMETA(DisplayName = "Attacking"),
	ECS_Dead UMETA(DisplayName = "Dead"),
	ECS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class ECharacterCombatState : uint8
{
	ECCS_OutCombat UMETA(DisplayName = "OutCombat"), // 脱战
	ECCS_InCombat UMETA(DisplayName = "InCombat"),	// 战斗中
	ECCS_Dead UMETA(DisplayName = "Dead"),
	ECCS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class ECharacterMotionState : uint8
{
	ECMS_Normal UMETA(DisplayName = "Normal"),		// 在地面上运动
	ECMS_Flying UMETA(DisplayName = "Flying"),
	ECMS_Climbing UMETA(DisplayName = "Climbing"),
	ECMS_Swiming UMETA(DisplayName = "Swiming"),
	ECMS_Riding UMETA(DisplayName = "Riding"),
	ECMS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EDeathPose : uint8
{
	EDP_Death1 UMETA(DisplayName = "Death1"),
	EDP_Death2 UMETA(DisplayName = "Death2"),
	EDP_Death3 UMETA(DisplayName = "Death3"),
	EDP_Death4 UMETA(DisplayName = "Death4"),
	EDP_Death5 UMETA(DisplayName = "Death5"),
	EDP_Death6 UMETA(DisplayName = "Death6"),
	EDP_MAX UMETA(DisplayName = "DefaultMAX")
};
