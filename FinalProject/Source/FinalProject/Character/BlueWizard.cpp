// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueWizard.h"
#include "../Weapon/MagicStaff.h"
#include "WizardPlayerState.h"

ABlueWizard::ABlueWizard()
{
	// Blue Wizard Character Mesh Set
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh{ TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Character/Animation/SM_Wizard.SM_Wizard'") };
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
	
	// Animation Class Set
	mAnimInstance = Cast<UWizardAnimInstance>(GetMesh()->GetAnimInstance());

	// Weapon Set
	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mWeapon = GetWorld()->SpawnActor<AMagicStaff>(FVector::ZeroVector, FRotator::ZeroRotator,param);
	mWeapon->SetMesh(mWeaponMesh);
	mWeapon->SetInputActionBind(this);
	mWeapon->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	
}

void ABlueWizard::NormalAttack()
{
	// Damage
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAttackAnimation(0);

		// Attack Collision Check
		FCollisionQueryParams	param(NAME_None, false, this);

		// Get Wizard State
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		FVector	StartLocation = GetActorLocation();
		FVector MeshForwardVector = GetMesh()->GetForwardVector();
		FQuat QuatRotation = FQuat(FRotator(0.0f, 90.0f, 0.0f));
		FVector PlayerForwardVector = QuatRotation.RotateVector(MeshForwardVector);
		FVector	EndLocation = StartLocation + PlayerForwardVector * State->mNormalAttackDistance;
		TArray<FHitResult>	resultArray;
		bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray,
			StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel3,
			FCollisionShape::MakeSphere(50.f), param);

		IsCollision ? GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Attack")))
			: GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Green, FString::Printf(TEXT("Attack Missed")));

#if ENABLE_DRAW_DEBUG

		// 구를 그린다.
		FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

		DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
			/* Radius */50.f / 2.f, /* Radius */50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
			DrawColor, false, 1.f);

#endif

		if (IsCollision)
		{
			for (int32 i = 0; i < resultArray.Num(); ++i)
			{
				// Attack Damage
				FDamageEvent DmgEvent;
				resultArray[i].GetActor()->TakeDamage((float)State->mNormalAttackPoint, DmgEvent, GetController(), this);

				// 이펙트 출력 및 사운드 재생.
			}
		}
	}
}

void ABlueWizard::FirstSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAttackAnimation(1);
	}
}

void ABlueWizard::SecondSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAttackAnimation(2);
	}
}

void ABlueWizard::ThirdSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAttackAnimation(3);
	}
}

void ABlueWizard::FourthSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAttackAnimation(4);
	}
}
