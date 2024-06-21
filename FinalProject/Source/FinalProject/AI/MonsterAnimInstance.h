// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Sleep,
	Attack,
	TakeDamage,
	Death,
	Spawn
};

enum class EBossCondition : uint8
{
	Nomal = 3,	// Skill Num
	Angry = 4,
	Danger = 5
};


UCLASS()
class FINALPROJECT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double mPlayerMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	EMonsterAnimType mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool mLoopAnimation = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	float PlayRate = 1.f;

	clock_t StartTime = 0;
	clock_t EndTime = 0;
	float PlayTime = 0.f;
	// 프레임 수
	float FrameFPS = 30.f;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> mIdleMontageArray;
	int32 mIdleIndex = 0;
	TArray<int32> mIdleIndexArray;
	int32 mIdleCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UAnimMontage*> mBossSkillMontageArray;
	int32 mSkillIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool mPlaySkill = false;

	EBossCondition BossCondition;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void PlayIdleMontage();
	void PlaySkillMontage(uint8 BossState);

	void SetBossCondition(EBossCondition Condition)
	{
		BossCondition = Condition;
	}

	EBossCondition GetBossCondition()
	{
		return BossCondition;
	}

	int32 GetSkillMontageIndex()
	{
		return mSkillIndex;
	}

public:
	void SetAnimSpeed(int32 Speed)
	{
		if (FrameFPS > 0.f)
		{
			PlayRate = FMath::Clamp<float>((float)Speed / FrameFPS, 1.f, 2.f);
		}
	}

	void ChangeAnimType(EMonsterAnimType Type)
	{
		mAnimType = Type;
	}

	const uint8 GetAnimType()
	{
		return (uint8)mAnimType;
	}

	void ChangeAnimLoop(bool Loop)
	{
		mLoopAnimation = Loop;
	}

public:
	UFUNCTION()
	void AnimNotify_AnimStart();

	UFUNCTION()
	void AnimNotify_AnimEnd();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_HitReactStart();

	UFUNCTION()
	void AnimNotify_HitReactEnd();

public:
	UFUNCTION()
	void AnimNotify_SKillStart();

	UFUNCTION()
	void AnimNotify_SkillEnd();

	UFUNCTION()
	void AnimNotify_ParticleStart();

	UFUNCTION()
	void AnimNotify_ParticleEnd();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
