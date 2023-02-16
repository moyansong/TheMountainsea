// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyActorComponent.h"
#include "../Characters/CharacterTypes.h"
#include "MotionComponent.generated.h"

class AMyCharacter;
class UCameraComponent;
class UCapsuleComponent;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEMOUNTAINSEA_API UMotionComponent : public UMyActorComponent
{
	GENERATED_BODY()

public:	
	friend class AMyCharacter;
	friend class APlayerCharacter;

	UMotionComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//------------------------------------------Set && Get---------------------------------------------------------

	void SetCharacterMotionState(ECharacterMotionState State);
	FORCEINLINE ECharacterMotionState GetCharacterMotionState() const { return CharacterMotionState; }

//------------------------------------------Functions---------------------------------------------------------

	void Fly();			// 正在飞行则取消飞行，普通状态则进入飞行，外部可调用
	void FlyStart();	// 立刻开始飞行，外部可调用
	void FlyStop();		// 立刻停止飞行，外部可调用

	void FlyForward(float Value);

protected:
	virtual void BeginPlay() override;

	void Flying(float DeltaTime);

	void OnCharacterMotionStateSet();

	void HandleNormalStart();

	void HandleFlyStart();
	void HandleFlyStop();

//------------------------------------------RPC---------------------------------------------------------
	UFUNCTION(Server, Reliable)
	void ServerSetCharacterMotionState(ECharacterMotionState State);

//------------------------------------------Parameters---------------------------------------------------------

private:
	UPROPERTY()
	TWeakObjectPtr<UCameraComponent> MyFollowCamera;

	UPROPERTY()
	TWeakObjectPtr<UCapsuleComponent> MyCapsuleComponent;

	UPROPERTY()
	TWeakObjectPtr<UCharacterMovementComponent> MyMovementComponent;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterMotionState, VisibleAnywhere, Category = Parameter)
	ECharacterMotionState CharacterMotionState = ECharacterMotionState::ECMS_Normal;
	UFUNCTION()
	void OnRep_CharacterMotionState(ECharacterMotionState OldState);

	ECharacterMotionState LastCharacterMotionState = ECharacterMotionState::ECMS_Normal;

	UPROPERTY(VisibleAnywhere, Category = Parameter)
	FVector2D RotationRate;

	FTimerHandle FlyTimer;
};
