// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss_RamPage.h"
#include "BossAIController.h"
#include "MonsterAnimInstance.h"
#include "MonsterState.h"

#include "../Effect/EffectBase.h"
#include "../Effect/Effect_FireEmit.h"


ABoss_RamPage::ABoss_RamPage()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Skins/Tier2/Elemental/Meshes/Rampage_Elemental.Rampage_Elemental'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/Monster/Animation/RamPage/AB_RamPage.AB_RamPage_C'"));

	if (AnimAsset.Succeeded())
		mMesh->SetAnimInstanceClass(AnimAsset.Class);

	AIControllerClass = ABossAIController::StaticClass();

	mCapsule->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	mCapsule->SetCapsuleHalfHeight(100.f);
	mCapsule->SetCapsuleRadius(100.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -100.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));

	mTableRowName = TEXT("Boss_Rampage");
}

void ABoss_RamPage::BeginPlay()
{
	Super::BeginPlay();

	mMonsterState = GetState<UMonsterState>();

	ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

	//PlaySkillMontage((uint8)EBossCondition::Nomal);
}

void ABoss_RamPage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsValid(mMonsterState) || !IsValid(mAnimInst))
		return;

	if (!mAnimInst->IsMontagePlaying())
	{
		if (!SkillEnable)
		{
			ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

			if (ChangeAnimCnt < ChangeAnimMaxCnt)
			{
				++ChangeAnimCnt;
				GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Blue, FString::Printf(TEXT("ChangeAnimCnt : %d"), ChangeAnimCnt));
				PlayIdleMontage();
			}
			else
			{
				SkillEnable = true;
				ChangeAnimCnt = 0;
			}
		}
		else
		{
			SkillEnable = false;
			ChangeAnimCnt = 0;
			ChangeAIAnimType((uint8)EMonsterAnimType::Skill);

			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, FString::Printf(TEXT("mHPPercent : %f"), mMonsterState->GetAIHPPercent()));
			if (mMonsterState->GetAIHPPercent() <= 0.3f)
			{
				PlaySkillMontage((uint8)EBossCondition::Danger);
				ChangeAnimMaxCnt = ChangeAnimMaxCnt = FMath::RandRange(0, 1);
			}
			else if (mMonsterState->GetAIHPPercent() <= 0.7f)
			{
				PlaySkillMontage((uint8)EBossCondition::Angry);
				ChangeAnimMaxCnt = 1;
			}
			else if (mMonsterState->GetAIHPPercent() <= 1.f)
			{

				PlaySkillMontage((uint8)EBossCondition::Nomal);
				// Idle 최대 2번까지
				ChangeAnimMaxCnt = FMath::RandRange(1, 2);
			}
		}
	}
}

void ABoss_RamPage::SkillSetting(int32 Num)
{
	int32 SkillIndex = Num;

	switch (SkillIndex)
	{
	case 0:
	{
		break;
	}
	case 1:
		break;
	case 2:
	{
		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		mEmitEffect = GetWorld()->SpawnActor<AEffect_FireEmit>(AEffect_FireEmit::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);

		float CapsuleHalfHeight = mEmitEffect->GetCapsuleHalfHeight();

		mEmitEffect->SetActorRelativeLocation(FVector(0.f, CapsuleHalfHeight, 0.f));

		if (mMesh->DoesSocketExist(TEXT("EmitSkill_Socket")))
			mEmitEffect->AttachToComponent(mMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("EmitSkill_Socket"));

		SkillActor = Cast<AActor>(mEmitEffect);

		break;
	}
	case 3:
		break;
	case 4:
		break;
	default: 
		break;
	}


}

