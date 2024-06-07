// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueWizard.h"
#include "../Weapon/MagicStaff.h"
#include "WizardPlayerState.h"


#include "../AI/AIMonsterPawn.h"
#include "../FXV/Storm.h"
#include "../FXV/Thunder.h"


ABlueWizard::ABlueWizard()
{
	// Blue Wizard Character Mesh Set
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh{ TEXT("/Script/Engine.SkeletalMesh'/Game/Blueprint/Character/Animation/SM_Wizard.SM_Wizard'") };
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMesh{ TEXT("/Script/Engine.StaticMesh'/Game/Blueprint/Character/Weapon/BlueStaff.BlueStaff'") };
	if (WeaponMesh.Succeeded())
	{
		mWeaponMesh = WeaponMesh.Object;
	}

	mFirstSkillParticle = AStorm::StaticClass();
	mSecondSkillParticle = AThunder::StaticClass();
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

void ABlueWizard::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	mWeapon->Destroy();
}

void ABlueWizard::NormalAttack()
{
	// Damage
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAnimation(EWizardAttackAnimTypes::NormalAttack);

		// Get Wizard State
		AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		// Attack Collision Check
		FCollisionQueryParams	param(NAME_None, false, this);
		FVector	EndLocation = GetActorLocation() + GetActorForwardVector() * State->mNormalAttackDistance;
		TArray<FHitResult>	resultArray;

		bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray,
			GetActorLocation(), 
			EndLocation, 
			FQuat(GetActorForwardVector(), FMath::DegreesToRadians(90.0f)), //Rotator
			ECC_GameTraceChannel3,
			FCollisionShape::MakeCapsule(FVector(50, 50, 125)), // (Radius, Radius, HalfHeight)
			param);

#if ENABLE_DRAW_DEBUG

		// 구를 그린다.
		FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

		DrawDebugCapsule(GetWorld(), 
			(GetActorLocation() + EndLocation) / 2.f,
			/* HalfHeight */ 125.f,
			/* Radius */ 50.f, 
			FQuat(GetActorForwardVector(), FMath::DegreesToRadians(90.0f)), //Rotator
			DrawColor, false, 1.f);

#endif

		if (IsCollision)
		{
			AAIMonsterPawn* Monster;
			for (int32 i = 0; i < resultArray.Num(); ++i)
			{
				// Attack Damage
				FDamageEvent DmgEvent;
				Monster = Cast<AAIMonsterPawn>(resultArray[i].GetActor());

				if (HasAuthority())
					Monster->TakeDamage((float)State->mNormalAttackPoint, DmgEvent, GetController(), this);
				else
					ServerAttack(Monster, (float)State->mNormalAttackPoint, DmgEvent, GetController(), this);

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
		mAnimInstance->PlayAnimation(EWizardAttackAnimTypes::FirstSkill);

		// Respawn Skill
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// Get Wizard State
			AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

			// Spawn Rotation
			FRotator SpawnRotation = FRotator::ZeroRotator;

			// Spawn Location
			FVector	EndLocation = GetActorLocation() + GetActorForwardVector() * State->mFirstSkillAttackDistance;
			FVector SpawnLocation = (GetActorLocation() + EndLocation) / 2.f;
			SpawnLocation.Z = 0.f;

			// Spawn Parameter
			FActorSpawnParameters ActorSpawnParam;
			ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// Skill Spawn
			AStorm* Storm = World->SpawnActor<AStorm>(mFirstSkillParticle, SpawnLocation, SpawnRotation, ActorSpawnParam);
			Storm->mMoveDir = GetActorForwardVector();
			Storm->SkillOwner = this;
			Storm->SkillDamage = State->mFirstSkillAttackDamage;

			// Use MP
			State->mMP -= 50; // TODO : MP사용량 나중에 추후 수정
		}
	}
}

void ABlueWizard::SecondSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAnimation(EWizardAttackAnimTypes::SecondSkill);

		// Respawn Skill
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			// Get Wizard State
			AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

			// Spawn Rotation
			FRotator SpawnRotation = GetActorRotation();

			// Spawn Location
			FVector	EndLocation = GetActorLocation() + GetActorForwardVector() * State->mSecondSkillAttackDistance;
			FVector SpawnLocation = (GetActorLocation() + EndLocation) / 2.f;
			SpawnLocation.Z = 0.f;

			// Spawn Parameter
			FActorSpawnParameters ActorSpawnParam;
			ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// Skill Spawn
			AThunder* Thunder = World->SpawnActor<AThunder>(mSecondSkillParticle, SpawnLocation, SpawnRotation, ActorSpawnParam);
			Thunder->SkillOwner = this;
			Thunder->SkillDamage = State->mSecondSkillAttackDamage;
			Thunder->Job = State->mJob;

			// Use MP
			State->mMP -= 50; // TODO : MP사용량 나중에 추후 수정
		}
	}
}

void ABlueWizard::ThirdSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAnimation(EWizardAttackAnimTypes::ThirdSkill);
	}
}

void ABlueWizard::FourthSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		mAnimInstance->PlayAnimation(EWizardAttackAnimTypes::FourthSkill);
	}
}