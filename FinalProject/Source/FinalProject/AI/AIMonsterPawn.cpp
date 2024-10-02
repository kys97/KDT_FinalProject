// Fill out your copyright notice in the Description page of Project Settings.

#include "AIMonsterPawn.h"
#include "DefaultAIController.h"
#include "MonsterAnimInstance.h"
#include "MonsterState.h"
#include "BossAIController.h"
#include "../UI/AIHUDWidget.h"
#include "../UI/DamageText.h"

#include "../FXV/HPPotionItem.h"
#include "../FXV/MPPotionItem.h"
#include "../FXV/AttackDamageUpgradeItem.h"
#include "../FXV/ArmorPointUpgradeItem.h"



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

	AIControllerClass = ADefaultAIController::StaticClass();

	mCapsule->SetCollisionProfileName(TEXT("Monster"));
	mCapsule->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	mState = CreateDefaultSubobject<UMonsterState>(TEXT("MonsterState"));
	static ConstructorHelpers::FObjectFinder<UDataTable>	MonsterTable(TEXT("/Script/Engine.DataTable'/Game/AI/Monster/DT_MonsterData.DT_MonsterData'"));
	// static 포인터 변수에 지정된 값이 없고, 데이터 테이블이 정상적으로 불러와졌다면
	if (!IsValid(mMonsterDataTable) && MonsterTable.Succeeded())
		mMonsterDataTable = MonsterTable.Object;
}

void AAIMonsterPawn::BeginPlay()
{
	Super::BeginPlay();
	AIControllerClass = ADefaultAIController::StaticClass();

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

	// HPBar가 띄워져 있는데 타겟이 사라지면 10초 뒤에 안보이도록
	if (mHPWidgetVisible)
	{
		ADefaultAIController* AIController = Cast<ADefaultAIController>(GetController());
		
		if (IsValid(AIController))
		{
			UObject* Object = AIController->GetBlackboardComponent()->GetValueAsObject(TEXT("Target"));

			if (Object == nullptr)
			{
				mHPWidgetTime += DeltaTime;
				if (mHPWidgetTime >= 10.f)
					SetHPWidgetVisible(false);
			}
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

	mMonsterState = GetState<UMonsterState>();

	Damage -= (float)mMonsterState->GetArmorPower();
	Damage = Damage < 1.f ? 1.f : Damage;

	mMonsterType = GetMonsterType();


	if (mMonsterState->GetAIHP() > 0)
		SpawnDamageText(Damage);

	if (mMonsterType == EMonsterType::Nomal)
		NomalMonsterTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	else if (mMonsterType == EMonsterType::Boss)
		BossMonsterTakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	return Damage;
}

void AAIMonsterPawn::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mOverlap = true;
}

void AAIMonsterPawn::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mOverlap = false;
}

void AAIMonsterPawn::NomalMonsterTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ADefaultAIController* AIController = Cast<ADefaultAIController>(GetController());
	
	SetHPWidgetVisible(true);

	if (!IsValid(AIController))
		return;

	if (mMonsterState->GetAIHP() > 0)
	{
		// Wizard Exp Set
		AWizard* Attacker = Cast<AWizard>(DamageCauser);
		FAttackerInfo NewAttacker;
		if (mMonsterState->GetAIHP() - Damage > 0)
			NewAttacker = FAttackerInfo(Attacker, Damage);
		else
			NewAttacker = FAttackerInfo(Attacker, mMonsterState->GetAIHP());
		Attackers.Add(NewAttacker);


		mMonsterState->ChangeHP(-Damage);

		mHPBar->SetAIHP(mMonsterState->GetAIHPPercent());

		if (Damage >= mMonsterState->GetArmorPower())
		{
			ChangeAnimLoop(true);
			ChangeAIAnimType((uint8)EMonsterAnimType::TakeDamage);

			if (IsAttackEnable())
				SetBlackboardValue(EventInstigator, AIController);

			SetReactLocation(DamageCauser);
		}

		if (mMonsterState->GetAIHP() <= 0)
		{
			SetBlackboardValue(nullptr, AIController);
			mCapsule->bApplyImpulseOnDamage = false;

			ChangeAIAnimType((uint8)EMonsterAnimType::Death);
			mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			mCapsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			AIController->UnPossess();
			AIController->StopAI();

			// Item Spawn
			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters ActorSpawnParam;
				ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	
				switch (FMath::RandRange(1, 4))
				{
				case 1:
					World->SpawnActor<AHPPotionItem>(
						AHPPotionItem::StaticClass(),
						GetActorLocation(),
						GetActorRotation(),
						ActorSpawnParam);
					break;
				case 2:
					World->SpawnActor<AMPPotionItem>(
						AMPPotionItem::StaticClass(),
						GetActorLocation(),
						GetActorRotation(),
						ActorSpawnParam);
					break;
				case 3:
					World->SpawnActor<AAttackDamageUpgradeItem>(
						AAttackDamageUpgradeItem::StaticClass(),
						GetActorLocation(),
						GetActorRotation(),
						ActorSpawnParam);
					break;
				case 4:
					World->SpawnActor<AArmorPointUpgradeItem>(
						AArmorPointUpgradeItem::StaticClass(),
						GetActorLocation(),
						GetActorRotation(),
						ActorSpawnParam);
					break;
				}
			}

			// Exp
			for (int i = 0; i < Attackers.Num(); i++)
			{
				Attackers[i].Attacker->GetExp(Attackers[i].AttackDamage);
			}
		}
	}
}

void AAIMonsterPawn::BossMonsterTakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ABossAIController* BossController = Cast<ABossAIController>(GetController());

	if (!IsValid(BossController))
		return;

	if (mMonsterState->GetAIHP() > 0)
	{
		mMonsterState->ChangeHP(-Damage);
		mHPBar->SetAIHP(mMonsterState->GetAIHPPercent());

		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("Client Log! AAIMonsterPawn/Boss mHP : %d"), mMonsterState->GetAIHP()));
		UE_LOG(Network, Warning, TEXT("Server Log! AAIMonsterPawn/Boss mHP : %f"), mMonsterState->GetAIHP());

		if (Damage >= mMonsterState->GetArmorPower())
		{
			ChangeAIAnimType((uint8)EMonsterAnimType::TakeDamage);


			SetReactLocation(DamageCauser);
		}

		if (mMonsterState->GetAIHP() <= 0)
		{
			mCapsule->bApplyImpulseOnDamage = false;

			ChangeAIAnimType((uint8)EMonsterAnimType::Death);

			BossController->UnPossess();
			BossController->StopAI();
		}
	}
}

void AAIMonsterPawn::ChangeAIAnimType_Implementation(uint8 AnimType)
{
	if(IsValid(mAnimInst))
		mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
}

void AAIMonsterPawn::SetHPWidgetVisible(bool Visible)
{
	mHPWidgetVisible = Visible;
	mHPWidgetComp->SetVisibility(Visible);
}

void AAIMonsterPawn::SpawnDamageText(float Damage)
{
	FActorSpawnParameters SpawnParam;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	float AIHalfHeight = mCapsule->GetScaledCapsuleHalfHeight();

	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.Z += AIHalfHeight + 100.f;

	ADamageText* DamageText = GetWorld()->SpawnActor<ADamageText>(
		SpawnLocation,
		FRotator::ZeroRotator,
		SpawnParam);

	DamageText->SetDamage(Damage);
}

uint8 AAIMonsterPawn::GetAnimType()
{
	if (IsValid(mAnimInst))
		return mAnimInst->GetAnimType();
	else
		return uint8();
}

EMonsterType AAIMonsterPawn::GetMonsterType()
{
	return EMonsterType();
}

void AAIMonsterPawn::PlaySkillMontage_Implementation(uint8 BossState)
{
	if (IsValid(mAnimInst))
		mAnimInst->PlaySkillMontage(BossState);
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

	HitReactLocation = AILocation + Dir * (mMonsterState->GetAIAttackDistance() * 2.f);

	mTakeDamage = true;
	mTakeDamageTime = 0.f;
}

