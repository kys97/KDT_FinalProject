// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueWizard.h"
#include "../Weapon/MagicStaff.h"
#include "WizardPlayerState.h"


#include "../AI/AIMonsterPawn.h"
#include "../FXV/Storm.h"
#include "../FXV/Thunder.h"
#include "../FXV/AOE.h"


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
	mThirdSkillParticle = AAOE::StaticClass();
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
		PlayAttackAnimation(this, EWizardAttackAnimTypes::NormalAttack);

		// Get Wizard State
		// AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		// Attack Collision Check
		FCollisionQueryParams	param(NAME_None, false, this);
		FVector	EndLocation = GetActorLocation() + GetActorForwardVector() * mState->mNormalAttackDistance;
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
					Monster->TakeDamage((float)mState->mNormalAttackPoint, DmgEvent, GetController(), this);
				else
					ServerAttack(Monster, (float)mState->mNormalAttackPoint, DmgEvent, GetController(), this);

				// 이펙트 출력 및 사운드 재생.
			}
		}
	}
}

void ABlueWizard::FirstSkill()
{
	if (mFirstSkillRemindTime == 0)
	{
		// AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();

		if (mAnimInstance->AttackEnable() && mState->mMP > 50.f)
		{
			// Set Animation
			PlayAttackAnimation(this, EWizardAttackAnimTypes::FirstSkill);

			// Respawn Skill
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// Spawn Rotation
				FRotator SpawnRotation = FRotator::ZeroRotator;

				// Spawn Location
				FVector	EndLocation = GetActorLocation() + GetActorForwardVector() * mState->mFirstSkillAttackDistance;
				FVector SpawnLocation = (GetActorLocation() + EndLocation) / 2.f;
				SpawnLocation.Z = 0.f;

				ServerFirstSkillSpawn(this, SpawnLocation, SpawnRotation, mState->mFirstSkillAttackDamage);

				// Use MP
				mState->mMP -= 50; // TODO : MP사용량 나중에 추후 수정
			
				// Set MP UI
				SetMPUI(mState->mMP / mState->mMPMax);

				// Set Skill Cool Time UI
				UseFirstSkill(mState->mFirstSkillCoolTime);
			}
		}
	}
}

void ABlueWizard::SecondSkill()
{
	if(mSecondSkillRemindTime == 0)
	{
		// AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		if (mAnimInstance->AttackEnable() && mState->mMP > 50.f)
		{
			// Set Animation
			PlayAttackAnimation(this, EWizardAttackAnimTypes::SecondSkill);

			// Respawn Skill
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				// Spawn Rotation
				FRotator SpawnRotation = GetActorRotation();

				// Spawn Location
				FVector	EndLocation = GetActorLocation() + GetActorForwardVector() * mState->mSecondSkillAttackDistance;
				FVector SpawnLocation = (GetActorLocation() + EndLocation) / 2.f;
				SpawnLocation.Z = 0.f;

				ServerSecondSkillSpawn(this, SpawnLocation, SpawnRotation, mState->mSecondSkillAttackDamage);

				// Use MP
				mState->mMP -= 50; // TODO : MP사용량 나중에 추후 수정

				// Set HP UI
				SetMPUI(mState->mMP / mState->mMPMax);

				// Set Skill Cool Time UI
				UseSecondSkill(mState->mSecondSkillCoolTime);
			}
		}
	}
}

void ABlueWizard::ThirdSkill()
{
	if(mThirdSkillRemindTime == 0)
	{
		// AWizardPlayerState* State = GetPlayerState<AWizardPlayerState>();
		if (mAnimInstance->AttackEnable() && mState->mMP > 50)
		{
			// Set Animation
			PlayAttackAnimation(this, EWizardAttackAnimTypes::ThirdSkill);

			// Respawn Skill
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				ServerThirdSkillSpawn(this, GetActorLocation(), GetActorRotation(), mState->mThirdSkillAttackDamage);

				// Use MP
				mState->mMP -= 50; // TODO : MP사용량 나중에 추후 수정

				// Set HP UI
				SetMPUI(mState->mMP / mState->mMPMax);

				// Set Skill Cool Time UI
				UseThirdSkill(mState->mThirdSkillCoolTime);
			}
		}
	}
}
void ABlueWizard::FourthSkill()
{
	if (mAnimInstance->AttackEnable())
	{
		// Set Animation
		PlayAttackAnimation(this, EWizardAttackAnimTypes::FourthSkill);
	}
}



void ABlueWizard::PlayAttackAnimation(AWizard* TargetWizard, EWizardAttackAnimTypes AnimType)
{
	ChangeAttackAnimInstance(AnimType);
	
	if (!HasAuthority())
		ServerChangeAttackAnimInstance(TargetWizard, AnimType);
}


void ABlueWizard::ServerFirstSkillSpawn_Implementation(AWizard* SkillOwner, FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Spawn Parameter
		FActorSpawnParameters ActorSpawnParam;
		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Skill Spawn
		AStorm* Storm = World->SpawnActor<AStorm>(mFirstSkillParticle, SpawnLocation, SpawnRotation, ActorSpawnParam);
		Storm->mMoveDir = GetActorForwardVector();
		Storm->SkillOwner = SkillOwner;
		Storm->SkillDamage = SkillDamage;
	}
}


void ABlueWizard::ServerSecondSkillSpawn_Implementation(AWizard* SkillOwner, FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Spawn Parameter
		FActorSpawnParameters ActorSpawnParam;
		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Skill Spawn
		AThunder* Thunder = World->SpawnActor<AThunder>(mSecondSkillParticle, SpawnLocation, SpawnRotation, ActorSpawnParam);
		Thunder->SkillOwner = SkillOwner;
		Thunder->SkillDamage = SkillDamage;
	}
}


void ABlueWizard::ServerThirdSkillSpawn_Implementation(AWizard* SkillOwner, FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		// Spawn Parameter
		FActorSpawnParameters ActorSpawnParam;
		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// Skill Spawn
		AAOE* AOE = World->SpawnActor<AAOE>(mThirdSkillParticle, SpawnLocation, SpawnRotation, ActorSpawnParam);
		AOE->SkillOwner = SkillOwner;
		AOE->SkillDamage = SkillDamage;
	}
}