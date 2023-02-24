// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyPlayerController.h"
#include "UIPlayerController.generated.h"

class UMyAttributeSet;

/**
 * 专门负责设置人物的UI
 */
UCLASS()
class THEMOUNTAINSEA_API AUIPlayerController : public AMyPlayerController
{
	GENERATED_BODY()
	
public:
	AUIPlayerController();
	virtual void Tick(float DeltaTime) override;
	virtual void AcknowledgePossession(class APawn* P) override;
	virtual void AcknowledgePossession(APlayerCharacter* NewCharacter) override;
//------------------------------------------Set && Get---------------------------------------------------------
	void SetUIMana(float OldMana = 0.f);
	void SetUIHealth(float OldHealth = 0.f);

//------------------------------------------Functions---------------------------------------------------------

protected:
	virtual void BeginPlay() override;

//------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY()
	TWeakObjectPtr<UMyAttributeSet> MyAttributeSet;

private:

};
