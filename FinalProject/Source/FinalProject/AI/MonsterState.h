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

public:
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
	int32	mMP;

	UPROPERTY(EditAnywhere)
	int32	mMPMax;

	// 최대 이동 속도
	UPROPERTY(EditAnywhere)
	int32	mMaxMoveSpeed;

	// 공격 거리
	UPROPERTY(EditAnywhere)
	int32	mAttackDistance;

public:
	virtual void ChangeHP(float Event)
	{
		mHP += Event;

		if (mHP < 0)
			mHP = 0;
	}

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
