// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"
#include "AIMonsterPawn.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = EMonsterAnimType::Idle;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
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
