// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemObjects.h"
#include "../../TheMountainsea.h"
#include "../../Characters/MyCharacter.h"

AWeapon::AWeapon()
{
	EquipmentType = EEquipmentType::EET_Weapon;

	HitBox1 = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox1"));
	HitBox1->SetupAttachment(GetRootComponent());
	HitBox1->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	HitBox1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HitBox1->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	HitBox1->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	HitBoxs.Add(HitBox1);

	FieldSystem = CreateDefaultSubobject<UFieldSystemComponent>(TEXT("FieldSystem"));
	FieldSystem->SetupAttachment(GetRootComponent());

	RadialVector = CreateDefaultSubobject<URadialVector>(TEXT("RadialVector"));
	RadialFalloff = CreateDefaultSubobject<URadialFalloff>(TEXT("RadialFalloff"));
	FieldSystemMetaDataFilter = CreateDefaultSubobject<UFieldSystemMetaDataFilter>(TEXT("FieldSystemMetaDataFilter"));
}

void AWeapon::Test()
{
	
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	/*if (WeaponBox)
	{
		WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
		WeaponBox->OnComponentEndOverlap.AddDynamic(this, &AWeapon::OnBoxEndOverlap);
	}*/

	HitIgnoreActors.Add(GetOwner());
	HitIgnoreActors.Add(this);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SaveFramePackage();
	TraceHit();
}

void AWeapon::SaveFramePackage()
{
	FFramePackage FramePackage;
	for (auto HitBox : HitBoxs)
	{
		FBoxInformation BoxInfo;
		BoxInfo.Location = HitBox->GetComponentLocation();
		BoxInfo.Rotation = HitBox->GetComponentRotation();
		BoxInfo.BoxExtent = HitBox->GetScaledBoxExtent();
		FramePackage.HitBoxInfo.Add(BoxInfo);
	}
	PrevFramePackage = CurrFramePackage;
	CurrFramePackage = FramePackage;
}

void AWeapon::Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator)
{
	Super::Equip(InParent, InSocketName, NewOwner, NewInstigator);

	AttachToSocket(InParent, InSocketName);
}

void AWeapon::TraceHit()
{
	if (!bCanHit || !MyCharacter) return;

	for (int i = 0; i < CurrFramePackage.HitBoxInfo.Num(); ++i)
	{
		const FVector Start = PrevFramePackage.HitBoxInfo[i].Location;
		const FVector End = CurrFramePackage.HitBoxInfo[i].Location;

		FHitResult HitResult;
		UKismetSystemLibrary::BoxTraceSingle(
			this,
			Start,
			End,
			CurrFramePackage.HitBoxInfo[i].BoxExtent,
			CurrFramePackage.HitBoxInfo[i].Rotation,
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			HitIgnoreActors,
			EDrawDebugTrace::None,
			HitResult,
			true
		);
		if (HitResult.GetActor())
		{
			if (MyCharacter->GetController())
			{
				UGameplayStatics::ApplyDamage(
					HitResult.GetActor(),
					30.f,
					MyCharacter->GetController(),
					this,
					UDamageType::StaticClass()
				);
			}

			IHitInterface* HitInterface = Cast<IHitInterface>(HitResult.GetActor());
			if (HitInterface)
			{
				//HitInterface->GetHit(HitResult, GetOwner(), this);
			}
			HitIgnoreActors.AddUnique(HitResult.GetActor());
		}
	}
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AWeapon::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AWeapon::SetCanHit(bool bCanWeaponHit)
{
	bCanHit = bCanWeaponHit;
	if (!bCanHit)
	{
		HitIgnoreActors.SetNum(2, false);
	}
}

void AWeapon::CreateFields(const FVector& FieldLocation)
{
	RadialFalloff->SetRadialFalloff(
		1000000.f, 
		0.8f, 
		1.f, 
		0.f, 
		200.f, 
		FieldLocation,
		EFieldFalloffType::Field_FallOff_None
	);
	FieldSystem->ApplyPhysicsField(
		true,
		EFieldPhysicsType::Field_ExternalClusterStrain,
		nullptr,
		RadialFalloff
	);

	RadialVector->SetRadialVector(
		1500000, 
		FieldLocation
	);
	FieldSystem->ApplyPhysicsField(
		true,
		EFieldPhysicsType::Field_LinearForce,
		FieldSystemMetaDataFilter,
		RadialVector
	);

	/*DrawDebugSphere(
		GetWorld(),
		FieldLocation,
		30.f,
		12,
		FColor::Red,
		false,
		10.f
	);*/
}