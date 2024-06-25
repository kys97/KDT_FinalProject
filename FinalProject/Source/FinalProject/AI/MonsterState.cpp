// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterState.h"
#include "AIMonsterPawn.h"

UMonsterState::UMonsterState()
{
}

void UMonsterState::BeginPlay()
{
	Super::BeginPlay();

	const FMonsterData* Data = AAIMonsterPawn::FindMonsterData(mDataTableRowName);

	if (Data)
	{
		mName = Data->mName;
		mMoveSpeed = Data->mMoveSpeed;
		mInteractionDistance = Data->mDetectDistance;

		mAttackPower = Data->mAttackPower;
		mArmorPower = Data->mArmorPower;
		mHP = Data->mHPMax;
		mHPMax = Data->mHPMax;
		mHPPercent = Data->mHPMax / Data->mHPMax * 100;
		mMP = Data->mMPMax;
		mMPMax = Data->mMPMax;
		mMaxMoveSpeed = Data->mMaxMoveSpeed;
		mAttackDistance = Data->mAttackDistance;

		mSkill1_Power = Data->mSkill1_Power;
		mSkill2_Power = Data->mSkill2_Power;
		mSkill3_Power = Data->mSkill3_Power;
		mSkill4_Power = Data->mSkill4_Power;
		mSkill5_Power = Data->mSkill5_Power;
		mSkill6_Power = Data->mSkill6_Power;
	}
}

void UMonsterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMonsterState, mHP);
	DOREPLIFETIME(UMonsterState, mMP);
	DOREPLIFETIME(UMonsterState, mHPPercent);
}
