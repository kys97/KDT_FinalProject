// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueWizard.h"
#include "../Weapon/MagicStaff.h"
#include "WizardPlayerState.h"


#include "../FXV/Storm.h"


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
		mAnimInstance->PlayAnimation(EWizardAttackAnimTypes::NormalAttack);

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
			FVector MeshForwardVector = GetMesh()->GetForwardVector();
			FVector PlayerForwardVector = MeshForwardVector;
			PlayerForwardVector.X = (-1) * MeshForwardVector.Y;
			PlayerForwardVector.Y = MeshForwardVector.X;
			FVector	StartLocation = GetActorLocation();
			FVector	EndLocation = StartLocation + PlayerForwardVector * State->mFirstSkillAttackDistance;
			FVector SpawnLocation = (StartLocation + EndLocation) / 2.f;
			SpawnLocation.Z = 0.f;

			// Spawn Parameter
			FActorSpawnParameters ActorSpawnParam;
			ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// Skill Spawn
			AStorm* Storm = World->SpawnActor<AStorm>(mFirstSkillParticle, SpawnLocation, SpawnRotation, ActorSpawnParam);
			Storm->mMoveDir = PlayerForwardVector;
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
