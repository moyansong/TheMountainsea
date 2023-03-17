// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../Animations/Instances/MyAnimInstance.h"
#include "../TheMountainsea.h"
#include "../Items/Weapons/Weapon.h"
#include "../Components/CombatComponent.h"
#include "../Components/MotionComponent.h"
#include "../Components/EquipmentComponent.h"
#include "../Components/OverheadWidgetComponent.h"
#include "../Abilities/MyAbilitySystemComponent.h"
#include "../Abilities/MyGameplayAbility.h"
#include "../Abilities/MyAttributeSet.h"
#include "../Game/GameStates/MyGameState.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MaxFlySpeed = 2000.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 250.f;
	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	GetMesh()->SetCollisionObjectType(ECC_SkeletalMesh);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	MotionComponent = CreateDefaultSubobject<UMotionComponent>(TEXT("MotionComponent"));
	MotionComponent->SetIsReplicated(true);

	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	EquipmentComponent->SetIsReplicated(true);

	OverheadWidgetComponent = CreateDefaultSubobject<UOverheadWidgetComponent>(TEXT("OverheadWidgetComponent"));
	OverheadWidgetComponent->SetupAttachment(GetRootComponent());

	AbilitySystemComponent = CreateDefaultSubobject<UMyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// 在OwnerActor的构造方法中创建的AttributeSet会自动注册到ASC
	MyAttributeSet = CreateDefaultSubobject<UMyAttributeSet>(TEXT("AttributeSet"));
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CombatComponent)
	{
		CombatComponent->MyCharacter = this;
		CombatComponent->MyAbilitySystemComponent = AbilitySystemComponent;
	}
	if (MotionComponent)
	{
		MotionComponent->MyCharacter = this;
		MotionComponent->MyCapsuleComponent = GetCapsuleComponent();
		MotionComponent->MyMovementComponent = GetCharacterMovement();
	}
	if (EquipmentComponent)
	{
		EquipmentComponent->MyCharacter = this;
	}
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->MyCharacter = this;
	}
	if (OverheadWidgetComponent)
	{
		OverheadWidgetComponent->MyCharacter = this;
	}
}

void AMyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController); 
	
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (CombatComponent)
	{
		
	}
	if (EquipmentComponent)
	{
		EquipmentComponent->SpawnDefaultEquipments();
	}
	if (OverheadWidgetComponent)
	{
		
	}
	if (AbilitySystemComponent)
	{
		if (HasAuthority())
		{
			AbilitySystemComponent->InitAbilityActorInfo(this, this);
			AbilitySystemComponent->InitAbility();
		}
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAttributeSet->GetManaAttribute()).AddUObject(this, &AMyCharacter::OnManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAttributeSet->GetHealthAttribute()).AddUObject(this, &AMyCharacter::OnHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAttributeSet->GetDamageAttribute()).AddUObject(this, &AMyCharacter::OnDamageChanged);
	}

	// 注册AttribueSet
	TArray<UAttributeSet*> AttributeSets;
	AttributeSets.Add(MyAttributeSet);
	AbilitySystemComponent->SetSpawnedAttributes(AttributeSets);
	if (MyAttributeSet && HasAuthority())
	{
		MyAttributeSet->InitAttribute();
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AMyCharacter, CharacterState, COND_SimulatedOnly);
}

UAbilitySystemComponent* AMyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

AWeapon* AMyCharacter::GetWeapon() const
{
	return EquipmentComponent ? EquipmentComponent->Weapon : nullptr;
}

void AMyCharacter::SetWeaponCollision(bool bCanWeaponHit)
{
	if (EquipmentComponent)
	{
		EquipmentComponent->SetWeaponCollision(bCanWeaponHit);
	}
}

void AMyCharacter::SetOverheadWidgetVisibility(bool bVisibility)
{
	if (OverheadWidgetComponent)
	{
		OverheadWidgetComponent->SetVisibility(bVisibility);
	}
}

void AMyCharacter::SetCharacterState(ECharacterState State)
{
	if (CharacterState == State) return;

	// 这里先在本地进行修改
	// 由于CharacterState的复制条件为COND_SimulatedOnly，所以Server并不会再发送属性给本客户端
	// 即使复制条件不为COND_SimulatedOnly，Server依然发送了属性
	// 由于本地的CharacterState已经改变了，也不会调用OnRep_CharaState(OnRep_CharaState只有新旧值不一样时才调用)
	CharacterState = State;
	OnCharacterStateSet();
	if (!HasAuthority())
	{
		ServerSetCharacterState(State);
	}
}

void AMyCharacter::ServerSetCharacterState_Implementation(ECharacterState State)
{
	SetCharacterState(State);
}

void AMyCharacter::OnRep_CharacterState(ECharacterState OldState)
{
	OnCharacterStateSet();
}

void AMyCharacter::OnCharacterStateSet()
{
	switch (CharacterState)
	{
	case ECharacterState::ECS_OutCombat:
		break;
	case ECharacterState::ECS_InCombat:
		break;
	case ECharacterState::ECS_Dead:
		break;
	default:
		break;
	}
}

void AMyCharacter::SetCharacterMotionState(ECharacterMotionState State)
{
	if (MotionComponent)
	{
		MotionComponent->SetCharacterMotionState(State);
	}
}

ECharacterMotionState AMyCharacter::GetCharacterMotionState() const
{
	return MotionComponent ? MotionComponent->GetCharacterMotionState() : ECharacterMotionState::ECMS_Normal;
}

void AMyCharacter::SetCharacterCombatState(ECharacterCombatState State)
{
	if (CombatComponent)
	{
		CombatComponent->SetCharacterCombatState(State);
	}
}

ECharacterCombatState AMyCharacter::GetCharacterCombatState() const
{
	return CombatComponent ? CombatComponent->GetCharacterCombatState() : ECharacterCombatState::ECCS_OutCombat;
}

FName AMyCharacter::GetMontageCurrentSection(const UAnimMontage* Montage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		return AnimInstance->Montage_GetCurrentSection(Montage);
	}
	return FName();
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

ERelativeLocation AMyCharacter::GetReliativeLocation(const FVector& Location)
{
	const FVector Forward = GetActorForwardVector();
	const FVector LocationLowered(Location.X, Location.Y, GetActorLocation().Z);
	const FVector ToLocation = (LocationLowered - GetActorLocation()).GetSafeNormal();

	const double CosTheta = FVector::DotProduct(Forward, ToLocation);
	// Theta总是>0
	double Theta = FMath::RadiansToDegrees(FMath::Acos(CosTheta));

	// ue是左手系，叉乘遵循左手定则
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToLocation);
	Theta *= CrossProduct.Z < 0 ? -1.f : 1.f;

	ERelativeLocation RelativeLocation = ERelativeLocation::ERL_Back;
	if (Theta >= -45.f && Theta < 45.f)
	{
		RelativeLocation = ERelativeLocation::ERL_Front;
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		RelativeLocation = ERelativeLocation::ERL_Left;
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		RelativeLocation = ERelativeLocation::ERL_Right;
	}

	/*Cout(this, Section.ToString());
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + Forward * 60.f, 5.f, FColor::Red, 10.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + ToHit * 60.f, 5.f, FColor::Green, 10.f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), GetActorLocation() + CrossProduct * 60.f, 5.f, FColor::Blue, 10.f);*/
	return RelativeLocation;
}

FSimpleComboCheck* AMyCharacter::GetSimpleComboInfo(const FName& ComboName)
{
	return AbilitySystemComponent ? AbilitySystemComponent->GetSimpleComboInfo(ComboName) : nullptr;
}

void AMyCharacter::AnimSignal(EAnimSignalType AnimSignalType)
{
	K2_AnimSignal(AnimSignalType);
}

void AMyCharacter::AddAbility(TSubclassOf<UGameplayAbility> NewAbilityClass)
{
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->AddAbility(NewAbilityClass);
	}
}

FGameplayTag AMyCharacter::GetSkillTag(const FName& SkillName) const
{
	return AbilitySystemComponent ? AbilitySystemComponent->GetSkillTag(SkillName) : FGameplayTag();
}

FName AMyCharacter::GetActiveSkill() const
{
	return CombatComponent ? CombatComponent->GetActiveSkill() : FName();
}

FName AMyCharacter::GetLastActiveSkill() const
{
	return CombatComponent ? CombatComponent->GetLastActiveSkill() : FName();
}

void AMyCharacter::ActivateSkill(const FName& SkillName)
{
	if (CombatComponent)
	{
		CombatComponent->ActivateSkill(SkillName);
	}
}

void AMyCharacter::ComboShortPressed(const FName& ComboName)
{
	ActivateSkill(ComboName);
}

void AMyCharacter::ComboLongPressed(const FName& ComboName)
{
	ActivateSkill(ComboName);
}

void AMyCharacter::Fly()
{
}

void AMyCharacter::Dodge()
{
}

void AMyCharacter::OnManaChanged(const FOnAttributeChangeData& Data)
{
	if (CombatComponent)
	{
		CombatComponent->OnManaChanged(Data);
	}
}

void AMyCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (CombatComponent)
	{
		CombatComponent->OnHealthChanged(Data);
	}
	if (Data.NewValue <= 0.f)
	{
		Die();
	}
}

void AMyCharacter::OnDamageChanged(const FOnAttributeChangeData& Data)
{
	if (CombatComponent)
	{
		CombatComponent->OnDamageChanged(Data);
	}
}

float AMyCharacter::GetHealth() const
{
	return MyAttributeSet ? MyAttributeSet->GetHealth() : 0.f;
}

bool AMyCharacter::IsAlive() const
{
	return GetHealth() > 0.f;
}

FHitData AMyCharacter::GetHitData() const
{
	return CombatComponent ? CombatComponent->MyHitData : FHitData();
}

void AMyCharacter::Die()
{
	if (CombatComponent)
	{
		CombatComponent->Die();
	}
}

void AMyCharacter::GetHit(const FHitData& HitData)
{
	if (!IsAlive()) return;
	
	if (CombatComponent)
	{
		CombatComponent->GetHit(HitData);
	}
}
