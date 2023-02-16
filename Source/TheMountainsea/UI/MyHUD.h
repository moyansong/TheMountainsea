// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

class UGameMainWidget;

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	friend class AUIPlayerController;

	AMyHUD();
	virtual void DrawHUD() override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

//------------------------------------------------Fuhnctions--------------------------------------------------------------
	template<class WidgetT>
	WidgetT* CreateAndShowWidget(TSubclassOf<UUserWidget> WidgetClass = WidgetT::StaticClass(), int32 ZOrder = 0)
	{
		if (WidgetClass)
		{
			WidgetT* Widget = CreateWidget<WidgetT>(GetOwningPlayerController(), WidgetClass);
			if (Widget)
			{
				Widget->AddToViewport(ZOrder);
				return Widget;
			}
		}
		return nullptr;
	}

//------------------------------------------------Parameters--------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UGameMainWidget> GameMainWidgetClass;

	UGameMainWidget* GameMainWidget;
};
