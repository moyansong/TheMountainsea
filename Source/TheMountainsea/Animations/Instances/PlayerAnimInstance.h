// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyAnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UPlayerAnimInstance : public UMyAnimInstance
{
	GENERATED_BODY()
	
public:

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadWrite, Category = Paramters, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* MyPlayerCharacter;
};
