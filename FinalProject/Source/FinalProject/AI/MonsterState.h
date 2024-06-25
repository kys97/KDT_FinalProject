// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIState.h"
#include "MonsterState.generated.h"


UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class FINALPROJECT_API UMonsterState : public UAIState
{
	GENERATED_BODY()
	
public:
	UMonsterState();

protected:
	virtual void BeginPlay() override;

protected:
	// 공격력
	UPROPERTY(EditAnywhere)
	int32	mAttackPower;
	// 방어력
	UPROPERTY(EditAnywhere)
	int32	mArmorPower;

	UPROPERTY(EditAnywhere, Replicated)
	int32	mHP;

	UPROPERTY(EditAnywhere)
	int32	mHPMax;

	UPROPERTY(EditAnywhere, Replicated)
	float	mHPPercent;

	UPROPERTY(EditAnywhere, Replicated)
	int32	mMP;

	UPROPERTY(EditAnywhere)
	int32	mMPMax;

	// 최대 이동 속도
	UPROPERTY(EditAnywhere)
	int32	mMaxMoveSpeed;

	// 공격 거리
	UPROPERTY(EditAnywhere)
	int32	mAttackDistance;

	/*  스킬 공격력 */
	UPROPERTY(EditAnywhere)
	int32	mSkill1_Power = 200;
	UPROPERTY(EditAnywhere)
	int32	mSkill2_Power = 200;
	UPROPERTY(EditAnywhere)
	int32	mSkill3_Power = 200;
	UPROPERTY(EditAnywhere)
	int32	mSkill4_Power = 200;
	UPROPERTY(EditAnywhere)
	int32	mSkill5_Power = 200;
	UPROPERTY(EditAnywhere)
	int32	mSkill6_Power = 200;

public:
	virtual void ChangeHP(float Event)
	{
		mHP += Event;

		if (mHP < 0)
			mHP = 0;

		mHPPercent = (mHP / (float)mHPMax);
	}

	int32 GetAttackPower()
	{
		return mAttackPower;
	}

	int32 GetArmorPower()
	{
		return mArmorPower;
	}

	int32 GetAIHP()
	{
		return mHP;
	}

	int32 GetAIHPMax()
	{
		return mHPMax;
	}

	float GetAIHPPercent()
	{
		return mHPPercent;
	}

	int32 GetAIMaxMoveSpeed()
	{
		return mMaxMoveSpeed;
	}

	int32 GetAIAttackDistance()
	{
		return mAttackDistance;
	}

	int32 GetSkill1_Power()
	{
		return mSkill1_Power;
	}

	int32 GetSkill2_Power()
	{
		return mSkill2_Power;
	}

	int32 GetSkill3_Power()
	{
		return mSkill3_Power;
	}

	int32 GetSkill4_Power()
	{
		return mSkill4_Power;
	}

	int32 GetSkill5_Power()
	{
		return mSkill5_Power;
	}

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
