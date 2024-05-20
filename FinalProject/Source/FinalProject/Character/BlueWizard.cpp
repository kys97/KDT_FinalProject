// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueWizard.h"
#include "../Weapon/MagicStaff.h"

ABlueWizard::ABlueWizard()
{
	// Blue Wizard Character Mesh Set
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh{ TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Character/SM_Wizard.SM_Wizard'") };
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMesh{ TEXT("/Script/Engine.StaticMesh'/Game/Blueprint/Character/Weapon/BlueStaff.BlueStaff'") };
	if (WeaponMesh.Succeeded())
	{
		mWeaponMesh = WeaponMesh.Object;
	}
}

void ABlueWizard::BeginPlay()
{
	Super::BeginPlay();
	
	// Weapon Set
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mWeapon = GetWorld()->SpawnActor<AMagicStaff>(FVector::ZeroVector, FRotator::ZeroRotator,param);
	mWeapon->SetMesh(mWeaponMesh);
	mWeapon->SetInputActionBind(this);
	mWeapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	
}
