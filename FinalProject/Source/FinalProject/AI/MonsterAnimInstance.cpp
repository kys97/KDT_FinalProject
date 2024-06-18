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

void UMonsterAnimInstance::AnimNotify_AnimStart()
{
	StartTime = clock();
}

void UMonsterAnimInstance::AnimNotify_AnimEnd()
{
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

void UMonsterAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMonsterAnimInstance, mAnimType);
	DOREPLIFETIME(UMonsterAnimInstance, mLoopAnimation);
}
