// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "AIMonsterPawn.h"
#include "../Character/Wizard.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = EMonsterAnimType::Idle;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AWizard* PlayerCharacter = Cast<AWizard>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			mPlayerMoveSpeed = Movement->Velocity.Length();
			mPlayerMoveSpeed /= Movement->MaxWalkSpeed;
		}
	}

}

void UMonsterAnimInstance::PlayIdleMontage()
{
	if (mAnimPlay)
		return;

	mIdleIndex = mNextIdleIndex;
	// 몽타주가 재생되고 있는지 판단
	if (!Montage_IsPlaying(mIdleMontageArray[mIdleIndex]))
	{
		// 재생 시키기 전에 재생 위치를 처음으로 초기화
		Montage_SetPosition(mIdleMontageArray[mIdleIndex], 0.f);

		// 재생
		Montage_Play(mIdleMontageArray[mIdleIndex]);

		int32 RandNum = FMath::RandRange(1, mIdleMontageArray.Num());
		mIdleIndexArray.Add(RandNum);

		// 같은 Idle 모션은 최대 2번만 나올 수 있도록
		for (int32 Array : mIdleIndexArray)
		{
			if (Array == RandNum)
				++mIdleCount;

			if (mIdleCount > 2)
			{
				mIdleIndexArray.Remove(RandNum);
				++RandNum;
				mIdleIndexArray.Add(RandNum);

				break;
			}
		}
		mIdleCount = 0;

		// 배열 개수만큼 나눈 나머지는 인덱스 숫자
		mNextIdleIndex = (mIdleIndex + RandNum) % mIdleMontageArray.Num();
	}
}

void UMonsterAnimInstance::PlaySkillMontage(uint8 BossState)
{
	// 애니메이션 동작 중이면 return;
	if (mAnimPlay)
		return;

	mSkillIndex = mNextSkillIndex;

	// 몽타주가 재생되고 있는지 판단
	if (!Montage_IsPlaying(mBossSkillMontageArray[mSkillIndex]))
	{

		// 재생 시키기 전에 재생 위치를 처음으로 초기화
		Montage_SetPosition(mBossSkillMontageArray[mSkillIndex], 0.f);

		// 재생
		Montage_Play(mBossSkillMontageArray[mSkillIndex]);

		// 다음 공격 동작을 재생하기 위해 인덱스 변경
		// 다음 공격이 동일하지 않기 위해 최소값은 1
		// 최대값은 배열 개수 -1
		int32 RandNum = FMath::RandRange(1, (BossState - 1));
		mSkillIndexArray.Add(RandNum);

		// 같은 Idle 모션은 최대 2번만 나올 수 있도록
		for (int32 Array : mSkillIndexArray)
		{
			if (Array == RandNum)
				++mSkillCount;

			if (mSkillCount > 2)
			{
				mSkillIndexArray.Remove(RandNum);
				++RandNum;
				mSkillIndexArray.Add(RandNum);

				break;
			}
		}
		mSkillCount = 0;

		//// 배열 개수만큼 나눈 나머지는 인덱스 숫자
		mNextSkillIndex = (mSkillIndex + RandNum) % BossState;
	}
}

void UMonsterAnimInstance::AnimNotify_AnimStart()
{
	mAnimPlay = true;

	StartTime = clock();
}

void UMonsterAnimInstance::AnimNotify_AnimEnd()
{
	mAnimPlay = false;

	EndTime = clock();

	clock_t result = EndTime - StartTime;
	do { result *= 10; }
	while (result / CLOCKS_PER_SEC >= 10);

	PlayTime = (float)(result / CLOCKS_PER_SEC);

	FrameFPS = PlayTime * 30.f;
}

void UMonsterAnimInstance::AnimNotify_Attack()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->NormalAttack();
}

void UMonsterAnimInstance::AnimNotify_AttackEnd()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->SetAttackEnd(true);
}

void UMonsterAnimInstance::AnimNotify_DeathEnd()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->DeathEnd();
}

void UMonsterAnimInstance::AnimNotify_HitReactStart()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->SetAttackEnable(false);
	Pawn->SetStunState(true);

	mLoopAnimation = true;
}

void UMonsterAnimInstance::AnimNotify_HitReactEnd()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->SetAttackEnable(true);
	mLoopAnimation = false;

	Pawn->SetActorRotation(Pawn->GetCurrentRotation());
	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
}

void UMonsterAnimInstance::AnimNotify_ParticleStart()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->SkillSetting(mSkillIndex);
}

void UMonsterAnimInstance::AnimNotify_ParticleEnd()
{
	AAIMonsterPawn* Pawn = Cast<AAIMonsterPawn>(TryGetPawnOwner());

	Pawn->SkillDestroy(mSkillIndex);
}

void UMonsterAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMonsterAnimInstance, mAnimType);
	DOREPLIFETIME(UMonsterAnimInstance, mLoopAnimation);
	DOREPLIFETIME(UMonsterAnimInstance, PlayRate);
	DOREPLIFETIME(UMonsterAnimInstance, mAnimPlay);
}
