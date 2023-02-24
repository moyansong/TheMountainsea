// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../MyCharacter.h"
#include "PlayerCharacter.generated.h"

class AUIPlayerController;

UCLASS()
class THEMOUNTAINSEA_API APlayerCharacter : public AMyCharacter
{
	GENERATED_BODY()
public:
	APlayerCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//------------------------------------------Set && Get---------------------------------------------------------
	FORCEINLINE virtual USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE virtual UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	FORCEINLINE AActor* GetOverlappingActor() { return OverlappingActor; }
	FORCEINLINE void SetOverlappingActor(AActor* Actor) { OverlappingActor = Actor; }

//--------------------------------------------Functions---------------------------------------------------------
	// 在服务器和本地都会调用
	virtual void PossessedBy(AUIPlayerController* NewController);
	
	virtual void AnimSignal(EAnimSignalType AnimSignalType) override;

	virtual void Fly() override;

	virtual void Dodge() override;

protected:
	virtual void BeginPlay() override;

	virtual void Die() override;

	virtual void ComboShortPressed(const FName& ComboName) override;
	virtual void ComboLongPressed(const FName& ComboName) override;
//----------------------------------------------RPC-----------------------------------------------------------


//---------------------------------------------Inputs--------------------------------------------------------------
	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void TurnAtRate(float Rate);

	UFUNCTION()
	void LookUpAtRate(float Rate);

	UFUNCTION()
	virtual void JumpStart();
	UFUNCTION()
	virtual void JumpStop();

	UFUNCTION()
	void MouseLeftClickStart();
	UFUNCTION()
	void MouseLeftClickStop();

	UFUNCTION()
	void MouseRightClickStart();
	UFUNCTION()
	void MouseRightClickStop();

	UFUNCTION(BlueprintCallable)
	void Test();
//------------------------------------------Paramters---------------------------------------------------------
	// 在运行时选中角色，Detail面板里会显示
	UPROPERTY(VisibleInstanceOnly)
	AActor* OverlappingActor;

	UPROPERTY(VisibleAnywhere, Category = Parameter)
	bool bDisableGameplay = false;

	UPROPERTY()
	TWeakObjectPtr<AUIPlayerController> MyController;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	float TurnRateGamepad;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bWButtonPressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bSButtonPressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bDButtonPressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	bool bAButtonPressed;

private:
//-----------------------------------------Components---------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;
};
