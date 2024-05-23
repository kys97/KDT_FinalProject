// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAnimInstance.h"
#include "Wizard.h"

UWizardAnimInstance::UWizardAnimInstance()
{
	IsMove = false;
	IsAttack = false;
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


void UWizardAnimInstance::PlayNormalAttackAnimation()
{
	if (!Montage_IsPlaying(mNormalAttackMontage))
	{
		Montage_SetPosition(mNormalAttackMontage, 0.f);
		Montage_Play(mNormalAttackMontage);
	}
}
