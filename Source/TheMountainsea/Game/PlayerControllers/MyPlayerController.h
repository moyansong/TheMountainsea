// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AMyHUD;
class APawn;
class AMyCharacter;
class APlayerCharacter;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();
	virtual void Tick(float DeltaTime) override;

	// 本地调用
	virtual void AcknowledgePossession(APawn* P) override;

	// 服务器调用
	virtual void AcknowledgePossession(APlayerCharacter* NewCharacter);
//------------------------------------------Set && Get---------------------------------------------------------	
	FORCEINLINE AMyCharacter* GetTargetCharacter() const { return TargetCharacter.IsValid() ? TargetCharacter.Get() : nullptr; }

//------------------------------------------Functions---------------------------------------------------------

protected:
	virtual void BeginPlay() override;

//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY(VisibleANywhere, Category = Parameter)
	TWeakObjectPtr<AMyCharacter> TargetCharacter;

	UPROPERTY(VisibleANywhere, Category = Parameter)
	TWeakObjectPtr<APlayerCharacter> MyPlayerCharacter;

	UPROPERTY(VisibleANywhere, Category = Parameter)
	TWeakObjectPtr<AMyHUD> HUD;

private:
};
