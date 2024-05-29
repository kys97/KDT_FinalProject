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
		mMoveSpeed = Data->mMoveSpeed;
		mInteractionDistance = Data->mDetectDistance;

		mAttackPoint = Data->mAttackPoint;
		mArmorPoint = Data->mArmorPoint;
		mHP = Data->mHPMax;
		mHPMax = Data->mHPMax;
		mMP = Data->mMPMax;
		mMPMax = Data->mMPMax;
		mMaxMoveSpeed = Data->mMaxMoveSpeed;
		mAttackDistance = Data->mAttackDistance;
	}
}
