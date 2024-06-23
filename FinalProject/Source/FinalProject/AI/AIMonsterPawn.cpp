// Fill out your copyright notice in the Description page of Project Settings.

#include "AIMonsterPawn.h"
#include "DefaultAIController.h"
#include "MonsterAnimInstance.h"
#include "MonsterState.h"

UDataTable* AAIMonsterPawn::mMonsterDataTable = nullptr;

const FMonsterData* AAIMonsterPawn::FindMonsterData(
	const FString& Name)
{
	// 정상적으로 탐색이 되어서 찾았다면 찾아준 메모리 주소를 반환하고
	// 못찾았다면 nullptr을 반환한다.
	return mMonsterDataTable->FindRow<FMonsterData>(*Name, TEXT(""));
}

AAIMonsterPawn::AAIMonsterPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mState = CreateDefaultSubobject<UMonsterState>(TEXT("MonsterState"));
	//mAnimInst = CreateDefaultSubobject<UMonsterAnimInstance>(TEXT("MonsterAnimInstance"));

	AIControllerClass = ADefaultAIController::StaticClass();

	mCapsule->SetCollisionProfileName(TEXT("Monster"));
	mCapsule->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	static ConstructorHelpers::FObjectFinder<UDataTable> 
		MonsterTable(TEXT("/Script/Engine.DataTable'/Game/AI/Monster/DT_MonsterData.DT_MonsterData'"));

	// static 포인터 변수에 지정된 값이 없고, 데이터 테이블이 정상적으로 불러와졌다면
	if (!IsValid(mMonsterDataTable) && MonsterTable.Succeeded())
		mMonsterDataTable = MonsterTable.Object;

	mOverlap = false;

	mAttackEnd = false;
	mAttackEnable = true;

	mDeathEnd = false;
	mAccTime = 0.f;
	mDeadDuration = 5.f;

	mTakeDamage = false;
	mTakeDamageTime = 0.f;

	mStun = false;
}

void AAIMonsterPawn::ChangeAIAnimType_Implementation(uint8 AnimType)
{
	if(IsValid(mAnimInst))
		mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
}

uint8 AAIMonsterPawn::GetAnimType()
{
	if (IsValid(mAnimInst))
		return mAnimInst->GetAnimType();
	else
		return uint8();
}

void AAIMonsterPawn::PlaySkillMontage_Implementation(uint8 BossState)
{
	if (IsValid(mAnimInst))
		mAnimInst->PlaySkillMontage(BossState);
}

void AAIMonsterPawn::SkillSetting(int32 Num)
{
}

void AAIMonsterPawn::SkillDestroy()
{
}

void AAIMonsterPawn::ChangeAnimLoop_Implementation(bool Loop)
{
	if (IsValid(mAnimInst))
		mAnimInst->ChangeAnimLoop(Loop);
}

void AAIMonsterPawn::DeathEnd()
{
	mDeathEnd = true;
	mAccTime = 0.f;
}

void AAIMonsterPawn::NormalAttack()
{
}

void AAIMonsterPawn::SetBlackboardValue(const AController* EventInstigator, AController* AIController)
{
	ADefaultAIController* DefaultAIController = Cast<ADefaultAIController>(AIController);

	APawn* EnemyPawn;
	if (EventInstigator != nullptr)
		EnemyPawn = EventInstigator->GetPawn();
	else
		EnemyPawn = nullptr;

	DefaultAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), EnemyPawn);
	
	mSetBlackboardValue = true;
	mAccTime = 0.f;
}

void AAIMonsterPawn::SetMoveSpeed(float Speed)
{
	mMovement->MaxSpeed = Speed;

	if (IsValid(mAnimInst))
	{
		mAnimInst->SetAnimSpeed(Speed);
	}
}

void AAIMonsterPawn::SetReactLocation(AActor* DamageCauser)
{
	AILocation = GetActorLocation();
	FVector TargetLocation = DamageCauser->GetActorLocation();

	// 공격 방향을 구한다.
	FVector	Dir = AILocation - TargetLocation;
	Dir.Z = 0.0;

	Dir.Normalize();

	HitReactLocation = AILocation + Dir * (mMonsterState->mAttackDistance * 2.f);

	mTakeDamage = true;
	mTakeDamageTime = 0.f;
}

void AAIMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	mCapsule->bApplyImpulseOnDamage = true;

	mAnimInst = Cast<UMonsterAnimInstance>(mMesh->GetAnimInstance());

	mCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAIMonsterPawn::BeginOverlap);
}

void AAIMonsterPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// MonsterPawn의 자식 클래스에서 넘긴 행이름을
	// AIState 에 저장
	mState->mDataTableRowName = mTableRowName;
}

void AAIMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mCurrentRotaion = GetActorRotation();

	if (mSetBlackboardValue)
	{
		mAccTime += DeltaTime;

		if (mAccTime >= mBlackboardResetDuration)
		{
			mSetBlackboardValue = false;
			mAccTime = 0.f;
		}
	}

	if (mDeathEnd)
	{
		mAccTime += DeltaTime;

		if (mAccTime >= mDeadDuration)
		{
			Destroy();

			mDeathEnd = false;
			mAccTime = 0.f;
		}
	}

	if (mTakeDamage)
	{
		mTakeDamageTime += DeltaTime;

		float Alpha = mTakeDamageTime / 0.2f;

		FVector NewLocation = FMath::Lerp(AILocation, HitReactLocation, Alpha);

		SetActorLocation(NewLocation);

		if (mTakeDamageTime >= 0.2)
		{
			mTakeDamage = false;
			mTakeDamageTime = 0.f;
		}
	}
}

// 서버에서만 동작
float AAIMonsterPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	ADefaultAIController* AIController = Cast<ADefaultAIController>(GetController());

	if (!IsValid(AIController))
		return 0;

	mMonsterState = GetState<UMonsterState>();

	Damage -= (float)mMonsterState->mArmorPower;
	Damage = Damage < 1.f ? 1.f : Damage;

	if (mMonsterState->mHP > 0)
	{
		mMonsterState->ChangeHP(-Damage);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Client Log! AAIMonsterPawn/Monster mHP : %d"), mMonsterState->mHP));
		UE_LOG(Network, Warning, TEXT("Server Log! AAIMonsterPawn/Monster mHP : %f"), mMonsterState->mHP);

		if (Damage >= 10.f)
		{
			ChangeAnimLoop(true);
			ChangeAIAnimType((uint8)EMonsterAnimType::TakeDamage);

			if (IsAttackEnable())
				SetBlackboardValue(EventInstigator, AIController);

			SetReactLocation(DamageCauser);
		}

		if (mMonsterState->mHP <= 0)
		{
			SetBlackboardValue(nullptr, AIController);
			mCapsule->bApplyImpulseOnDamage = false;

			ChangeAIAnimType((uint8)EMonsterAnimType::Death);

			AIController->UnPossess();
			AIController->StopAI();
		}
	}

	return Damage;
}

void AAIMonsterPawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Monster BeginOverlap"));

	mOverlap = true;
}

void AAIMonsterPawn::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Monster End Overlap"));

	mOverlap = false;
}

