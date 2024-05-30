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
