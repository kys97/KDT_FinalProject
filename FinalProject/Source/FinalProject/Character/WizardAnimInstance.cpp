// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAnimInstance.h"
#include "Wizard.h"

UWizardAnimInstance::UWizardAnimInstance()
{
	IsMove = false;
	IsAttack = false;
	IsDeath = false;
	AttackIndex = 0;
}

void UWizardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UWizardAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsAttack)
	{
		AWizard* Character = Cast<AWizard>(TryGetPawnOwner());

		if (IsValid(Character))
		{
			UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
			if (IsValid(Movement))
			{
				if (Movement->Velocity.Length() > 0.0f)
					IsMove = true;
				else
					IsMove = false;
			}
		}
	}
}


void UWizardAnimInstance::AnimNotify_AttackStart()
{
	IsAttack = true;
}

void UWizardAnimInstance::AnimNotify_AttackEnd()
{
	IsAttack = false;
}

void UWizardAnimInstance::PlayAnimation(const EWizardAttackAnimTypes animType)
{
	AttackIndex = (int32)animType;

	if (!Montage_IsPlaying(mAttackMontageArray[AttackIndex]))
	{
		Montage_SetPosition(mAttackMontageArray[AttackIndex], 0.f);
		Montage_Play(mAttackMontageArray[AttackIndex]);
	}
}
