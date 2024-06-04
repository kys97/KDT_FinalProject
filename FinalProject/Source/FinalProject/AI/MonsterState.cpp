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

		mAttackPower = Data->mAttackPower;
		mArmorPower = Data->mArmorPower;
		mHP = Data->mHPMax;
		mHPMax = Data->mHPMax;
		mMP = Data->mMPMax;
		mMPMax = Data->mMPMax;
		mMaxMoveSpeed = Data->mMaxMoveSpeed;
		mAttackDistance = Data->mAttackDistance;
	}
}

void UMonsterState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMonsterState, mHP);
	DOREPLIFETIME(UMonsterState, mMP);
}
