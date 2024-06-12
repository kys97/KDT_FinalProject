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

	mDeathEnd = false;
	mAccTime = 0.f;
	mDeadDuration = 5.f;
}

void AAIMonsterPawn::ChangeAIAnimType_Implementation(uint8 AnimType)
{
	if(IsValid(mAnimInst))
		mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
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

	APawn* EnemyPawn = EventInstigator->GetPawn();

	DefaultAIController->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), EnemyPawn);
	mSetBlackboardValue = true;
}

void AAIMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

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
}

void AAIMonsterPawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Monster BeginOverlap"));

	mOverlap = true;
}

// 서버에서만 동작
float AAIMonsterPawn::TakeDamage(float Damage, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	Damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	ADefaultAIController* AIController = Cast<ADefaultAIController>(GetController());

	SetBlackboardValue(EventInstigator, AIController);

	mMonsterState = GetState<UMonsterState>();

	Damage -= mMonsterState->mArmorPower;
	Damage = Damage < 1.f ? 1.f : Damage;

	if (mMonsterState->mHP > 0 && !mDeathEnd)
	{
		mMonsterState->ChangeHP(-Damage);
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Client Log! AAIMonsterPawn/Monster mHP : %d"), mMonsterState->mHP));
		UE_LOG(Network, Warning, TEXT("Server Log! AAIMonsterPawn/Monster mHP : %d"), mMonsterState->mHP);

		if (mMonsterState->mHP <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Monster Dead"));
			UE_LOG(Network, Warning, TEXT("Server Log! AAIMonsterPawn/Monster Dead"));

			ChangeAIAnimType((uint8)EMonsterAnimType::Death);

			AIController->UnPossess();
		}
	}	

	return Damage;
}

void AAIMonsterPawn::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("Monster End Overlap"));

	mOverlap = false;
}

