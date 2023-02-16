// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class AMyHUD;
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

//------------------------------------------Set && Get---------------------------------------------------------	
	FORCEINLINE AMyCharacter* GetTargetCharacter() const { return TargetCharacter.IsValid() ? TargetCharacter.Get() : nullptr; }

//------------------------------------------Functions---------------------------------------------------------
	virtual void Init();

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
