// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THEMOUNTAINSEA_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	template<class T>
	T* GetHUD()
	{
		if (GetWorld())
		{
			return GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->GetHUD<T>() : nulltpr;
		}
		return nullptr;
	}

	template<class T>
	T* GetPlayerController()
	{
		return GetWorld() ? GetWorld()->GetFirstPlayerController<T>() : nullptr;
	}

	template<class T>
	T* GetPawn()
	{
		if (GetWorld())
		{
			return GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->GetPawn<T>() : nullptr;
		}
		return nullptr;
	}

	template<class T>
	T* GetGameInstance()
	{
		return GetWorld() ? GetWorld()->GetGameInstance<T>() : nullptr;
	}

	template<class T>
	T* GetPlayerState()
	{
		if (GetWorld())
		{
			return GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->GetPlayerState<T>() : nullptr;
		}
		return nullptr;
	}

};
