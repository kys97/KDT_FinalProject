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

	mTableRowName = TEXT("Dragon_SoulEater");
}

void ABoss_RamPage::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(mAnimInst))
		mAnimInst->SetBossCondition(EBossCondition::Nomal);
	//ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

	PlaySkillMontage((uint8)EBossCondition::Nomal);
}

void ABoss_RamPage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoss_RamPage::SkillSetting(int32 Num)
{
	int32 SkillIndex = Num;

	switch (SkillIndex)
	{
	case 0:
		//AEffect_FireEmit* FireEmit = Cast<AEffect_FireEmit>(mEffect);

		FActorSpawnParameters	SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		mEmitEffect = GetWorld()->SpawnActor<AEffect_FireEmit>(AEffect_FireEmit::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);
		
		//UCapsuleComponent* SkillCapsule = FireEmit->GetCapsule();
		//FVector SkillLocation = SkillCapsule->GetRelativeLocation();
		//SkillLocation.Y += SkillCapsule->GetScaledCapsuleHalfHeight();
		//SkillCapsule->SetRelativeLocation(SkillLocation);

		if (mMesh->DoesSocketExist(TEXT("EmitSkill_Socket")))
			mEmitEffect->AttachToComponent(mMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("EmitSkill_Socket"));

		break;
	//case 1:
	//	break;
	//case 2:
	//	break;
	//case 3:
	//	break;
	//case 4:
	//	break;
	//case 5:
	//	break;
	}


}

