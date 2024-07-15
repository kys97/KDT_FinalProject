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
	
	if (IsValid(BossController))
	{
		mHPBar = BossController->GetHPBarWidget();

		mHPBar->SetMonsterType(mMonsterType);
		if (mHPBar)
		{
			mHPBar->AddConstructDelegate<ABoss_RamPage>(this, &ABoss_RamPage::SetHPBar);
		}
	}

	ChangeAIAnimType((uint8)EMonsterAnimType::Spawn);
	mSpawn = true;

	mBodyCapsule->OnComponentBeginOverlap.AddDynamic(this, &ABoss_RamPage::AttackOverlap);
	mRightArm->OnComponentBeginOverlap.AddDynamic(this, &ABoss_RamPage::AttackOverlap);
	mLeftArm->OnComponentBeginOverlap.AddDynamic(this, &ABoss_RamPage::AttackOverlap);
}

void ABoss_RamPage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRandomStream RandomStream;
	RandomStream.Initialize(DeltaTime);

	if (!IsValid(mMonsterState) || !IsValid(mAnimInst))
		return;

	if (mSpawn)
		return;
	
	if (mState->GetAIHPPercent() > 0.f)
	{
		mChangeSkillTime += DeltaTime;

		if (mChangeSkillTime >= mChangeSkillDuration)
		{
			GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green, FString::Printf(TEXT("mHPPercent : %f"), mMonsterState->GetAIHPPercent()));
			if (mMonsterState->GetAIHPPercent() <= 0.3f)
			{
				PlaySkillMontage((uint8)EBossCondition::Danger);
				mChangeSkillDuration = 0.f;
			}
			else if (mMonsterState->GetAIHPPercent() <= 0.7f)
			{
				PlaySkillMontage((uint8)EBossCondition::Angry);
				mChangeSkillDuration = 5.f;
			}
			else if (mMonsterState->GetAIHPPercent() <= 1.f)
			{
				PlaySkillMontage((uint8)EBossCondition::Nomal);
			}
			mSkillEnable = false;
			mChangeSkillTime = 0;
		}

		ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
	}

	if (mDestroy)
	{
		mDestroyTime += DeltaTime;
		if (mDestroyTime >= mDestroyDuration)
		{
			for (int i = 0; i < SkillActorArray.Num(); ++i)
			{
				if (SkillActorArray[i] != nullptr)
				{
					SkillActorArray[i]->Destroy();
				}
			}
			SkillActorArray.SetNum(0);
			mDestroyTime = 0.f;
			mDestroy = false;
		}
	}
}

void ABoss_RamPage::AttackOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FDamageEvent DmgEvent;
	OtherActor->TakeDamage(mState->GetAttackPower(), DmgEvent, GetInstigatorController(), this);
}

void ABoss_RamPage::SkillSetting(int32 Num)
{
	switch (Num)
	{
	case 0:	{
		SpawnSkill_GroundSmash();
		break;
	}
	case 1:	{
		SpawnSkill_FireEmit();
		break;
	}
	case 2:	{
		SpawnSkill_Rolling();
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
	mDestroyTime = 0.f;
	mDestroyTime = false;
}

void ABoss_RamPage::SkillDestroy(int32 Num)
{
	switch (Num)
	{
	case 0: {
		SetDestroyDuration(5.f);
		break;
	}
	case 1: {
		SetDestroyDuration(0.f);
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;
	}
	case 4: {
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
	float BossHalfHeight = mBodyCapsule->GetScaledCapsuleHalfHeight();
	float BossRadius = mBodyCapsule->GetScaledCapsuleRadius();

	FVector SpawnCenter = GetActorLocation();

	float RandSpawnPointX = RandRangeNumber(1.f, 5.f);
	float RandSpawnPointY = RandRangeNumber(1.f, 2.f);

	FVector RandXY(RandSpawnPointX, RandSpawnPointY, 0.f);
	for (int i = 0; i < mRandXYArray.Num(); ++i)
	{
		if (mRandXYArray[i] == RandXY)
		{
			RandSpawnPointX = RandRangeNumber(1.f, 5.f);
			RandSpawnPointY = RandRangeNumber(1.f, 2.f);
		}
	}
	mRandXYArray.Add(RandXY);

	FVector SpawnPoint;
	SpawnPoint.X = SpawnCenter.X + BossRadius * 2.f * RandSpawnPointX;
	SpawnPoint.Y = SpawnCenter.Y + BossRadius * RandSpawnPointY;
	SpawnPoint.Z = BossHalfHeight * 2;

	mFallingStonEffect = GetWorld()->SpawnActor<AFallingSton>(AFallingSton::StaticClass(),
		FVector((SpawnPoint.X), (SpawnPoint.Y), (SpawnPoint.Z + (BossHalfHeight*2))),
		FRotator::ZeroRotator, SpawnParam);

	mFallingStonEffect->SetSkillPower(mState->GetSkill1_Power());

	SkillActorArray.Add(Cast<AActor>(mFallingStonEffect));
}

float ABoss_RamPage::RandRangeNumber(float Min, float Max)
{
	bool BoolResult = FMath::RandBool();
	float RandNum;
	if (BoolResult)
		RandNum = FMath::RandRange(Min, Max);
	else
		RandNum = FMath::RandRange(Min, Max) * -1.f;

	return RandNum;
}

void ABoss_RamPage::SpawnSkill_FireEmit()
{
	FActorSpawnParameters	SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	mEmitEffect = GetWorld()->SpawnActor<AEffect_FireEmit>(AEffect_FireEmit::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, SpawnParam);

	float CapsuleHalfHeight = mEmitEffect->GetCapsuleHalfHeight();

	if (mMesh->DoesSocketExist(TEXT("EmitSkill_Socket")))
		mEmitEffect->AttachToComponent(mMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("EmitSkill_Socket"));

	mEmitEffect->SetSkillPower(mState->GetSkill1_Power());

	SkillActorArray.Add(Cast<AActor>(mEmitEffect));
}

void ABoss_RamPage::SpawnSkill_Rolling()
{
	ABossAIController* BossController = Cast<ABossAIController>(GetController());

	AActor* Target = Cast<AActor>(BossController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (!IsValid(Target))
	{
		FVector MoveLocation = GetActorLocation() + GetActorForwardVector() * 1000.f;
		BossController->AIMoveToLocation(MoveLocation);
	}
	else
	{
		FVector MoveLocation = GetActorLocation() + GetActorForwardVector() * 1000.f;

		BossController->AIMoveToLocation(MoveLocation);
	}
}

void ABoss_RamPage::SpawnSkill_3()
{
}

void ABoss_RamPage::SpawnSkill_4()
{
}

