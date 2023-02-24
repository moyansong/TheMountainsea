// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

class AMyCharacter;
class APlayerCharacter;
class AMyPlayerController;
class AUIPlayerController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEMOUNTAINSEA_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyActorComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//------------------------------------------Functions---------------------------------------------------------
	UFUNCTION(BlueprintCallable, Category = Transformation)
	FVector GetOwnerLocation() const { return GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector; }
	UFUNCTION(BlueprintCallable, Category = Transformation)
	FRotator GetOwnerRotation() const { return GetOwner() ? GetOwner()->GetActorRotation() : FRotator::ZeroRotator; }
	UFUNCTION(BlueprintCallable, Category = Transformation)
	FVector GetOwnerForwardVector() const { return GetOwner() ? GetOwner()->GetActorForwardVector() : FVector::ZeroVector; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Networking)
	bool HasAuthority() const;

	UFUNCTION(BlueprintCallable, Category = Networking)
	bool IsLocallyControlled() const;

//-------------------------------------------Parameters---------------------------------------------------------
	UPROPERTY()
	TWeakObjectPtr<AMyCharacter> MyCharacter;

	UPROPERTY()
	TWeakObjectPtr<APlayerCharacter> MyPlayerCharacter;

	UPROPERTY()
	TWeakObjectPtr<AUIPlayerController> MyPlayerController;
};
