// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "../Characters/MyCharacter.h"
#include "../Characters/PlayerCharacters/PlayerCharacter.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	ItemMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = ItemMesh;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* OverlappingCharacter = Cast<APlayerCharacter>(OtherActor);
	if (OverlappingCharacter)
	{
		OverlappingCharacter->SetOverlappingActor(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* OverlappingCharacter = Cast<APlayerCharacter>(OtherActor);
	if (OverlappingCharacter)
	{
		if (OverlappingCharacter->GetOverlappingActor() == this)
		{
			OverlappingCharacter->SetOverlappingActor(nullptr);
		}
	}
}

void AItem::SetItemState(EItemState State)
{
	ItemState = State;
	OnItemStateChanged();
}

void AItem::OnItemStateChanged()
{
	switch (ItemState)
	{
	case EItemState::EIS_Initialized:
		OnInitialized();
		break;
	case EItemState::EIS_Owned:
		OnOwned();
		break;
	case EItemState::EIS_Dropped:
		OnDropped();
		break;
	}
}

void AItem::OnInitialized()
{
}

void AItem::OnOwned()
{
}

void AItem::OnDropped()
{
}