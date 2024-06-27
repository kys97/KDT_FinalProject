// Fill out your copyright notice in the Description page of Project Settings.

#include "Boss_RamPage.h"
#include "BossAIController.h"
#include "MonsterAnimInstance.h"
#include "MonsterState.h"

#include "../UI/AIHUDWidget.h"

#include "../Effect/EffectBase.h"
#include "../Effect/Effect_FireEmit.h"
#include "../Effect/FallingSton.h"


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
	mCapsule->SetRelativeRotation(FRotator(0.f, 180.f, 0.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mCapsule->SetCapsuleHalfHeight(200.f);
	mCapsule->SetCapsuleRadius(100.f);

	mMesh->SetRelativeLocation(FVector(0.f, 0.f, -200.f));
	mMesh->SetRelativeRotation(FRotator(0.f, -90.f, 0.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mMesh->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	mMesh->SetCollisionProfileName(TEXT("Monster"));

	SetCapsuleCollision();

	mMonsterType = EMonsterType::Boss;

	mTableRowName = TEXT("Boss_Rampage");
}

void ABoss_RamPage::SetCapsuleCollision()
{
	mBodyCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("BodyAttack"));
	mBodyCapsule->SetupAttachment(mMesh);
	mBodyCapsule->SetCapsuleHalfHeight(100.f);
	mBodyCapsule->SetCapsuleRadius(100.f);
	mBodyCapsule->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	mBodyCapsule->SetCollisionProfileName(TEXT("MonsterAttack"));

	mRightArm = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RightArm"));
	mRightArm->SetupAttachment(mMesh, TEXT("RigthArm_Socket"));
	mRightArm->SetRelativeLocation(FVector(-5.f, 0.f, 0.f));
	mRightArm->SetRelativeRotation(FRotator(76.f, 0.f, 169.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mRightArm->SetCapsuleHalfHeight(45.f);
	mRightArm->SetCapsuleRadius(25.f);
	mRightArm->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	mRightArm->SetCollisionProfileName(TEXT("MonsterAttack"));

	mLeftArm = CreateDefaultSubobject<UCapsuleComponent>(TEXT("LeftArm"));
	mLeftArm->SetupAttachment(mMesh, TEXT("LeftArm_Socket"));
	mLeftArm->SetRelativeLocation(FVector(2.f, 0.f, 0.f));
	mLeftArm->SetRelativeRotation(FRotator(81.f, 0.f, 174.f)); // Pitch(Y), Yaw(Z), Roll(X)
	mLeftArm->SetCapsuleHalfHeight(46.f);
	mLeftArm->SetCapsuleRadius(25.f);
	mLeftArm->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	mLeftArm->SetCollisionProfileName(TEXT("MonsterAttack"));
}

void ABoss_RamPage::BeginPlay()
{
	Super::BeginPlay();

	mMonsterState = GetState<UMonsterState>();

	ABossAIController* BossController = Cast<ABossAIController>(GetController());
	mHPBar = BossController->GetHPBarWidget();

	mHPBar->SetMonsterType(mMonsterType);
	if (mHPBar)
	{
		mHPBar->AddConstructDelegate<ABoss_RamPage>(this, &ABoss_RamPage::SetHPBar);
	}

	ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

	mBodyCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABoss_RamPage::AttackOverlap);
	mRightArm->OnComponentBeginOverlap.AddDynamic(this, &ABoss_RamPage::AttackOverlap);
	mLeftArm->OnComponentBeginOverlap.AddDynamic(this, &ABoss_RamPage::AttackOverlap);

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
				ChangeAnimMaxCnt = 0;
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

void ABoss_RamPage::AttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Hit")));
}

void ABoss_RamPage::SkillSetting(int32 Num)
{
	int32 SkillIndex = Num;

	switch (SkillIndex)
	{
	case 0:	{
		SpawnSkill_GroundSmash();
		break;
	}
	case 1:	{
		SpawnSkill_1();
		break;
	}
	case 2:	{
		SpawnSkill_FireEmit();
		break;
	}
	case 3:	{
		SpawnSkill_3();
		break;
	}
	case 4:	{
		SpawnSkill_4();
		break;
	}
	default: 
		break;
	}


}

void ABoss_RamPage::SetHPBar()
{
	mHPBar->SetAIHP(mState->GetAIHPPercent());
}

void ABoss_RamPage::SpawnSkill_GroundSmash()
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Smash Effect
	FVector SpawnLocation = mMesh->GetSocketLocation(TEXT("L_GroundSmash_Socket"));
	float RandRocation = FMath::FRandRange(-180.f, 180.f);

	AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
		SpawnLocation,
		FRotator(0.f, 0.f, RandRocation),
		SpawnParam);

	float ScaleX = FMath::FRandRange(1.f, 2.f);
	float ScaleY = FMath::FRandRange(1.f, 2.f);
	Effect->SetActorScale3D(FVector(ScaleX, ScaleY, 1.f));
	Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/AI/Asset/Particle/P_Mace_Impact_Damage.P_Mace_Impact_Damage'"));

	// Ston Effect

	FVector SpawnCenter = GetActorLocation();
	SpawnCenter.Z += mCapsule->GetScaledCapsuleHalfHeight();

	float RandSpawnPoint = FMath::RandRange(-500.f, 500.f);

	mFallingStonEffect = GetWorld()->SpawnActor<AFallingSton>(AFallingSton::StaticClass(),
		FVector((SpawnCenter.X + RandSpawnPoint), (SpawnCenter.Y + RandSpawnPoint), (SpawnCenter.Z + 500.f)), FRotator::ZeroRotator, SpawnParam);

	SkillActor = Cast<AActor>(mFallingStonEffect);
}

void ABoss_RamPage::SpawnSkill_1()
{
}

void ABoss_RamPage::SpawnSkill_FireEmit()
{
	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	mEmitEffect = GetWorld()->SpawnActor<AEffect_FireEmit>(AEffect_FireEmit::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);

	float CapsuleHalfHeight = mEmitEffect->GetCapsuleHalfHeight();

	mEmitEffect->SetActorRelativeLocation(FVector(0.f, CapsuleHalfHeight, 0.f));

	if (mMesh->DoesSocketExist(TEXT("EmitSkill_Socket")))
		mEmitEffect->AttachToComponent(mMesh, FAttachmentTransformRules::KeepRelativeTransform, TEXT("EmitSkill_Socket"));

	SkillActor = Cast<AActor>(mEmitEffect);
}

void ABoss_RamPage::SpawnSkill_3()
{
}

void ABoss_RamPage::SpawnSkill_4()
{
}

