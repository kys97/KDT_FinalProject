// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAnimInstance.h"
#include "Wizard.h"

UWizardAnimInstance::UWizardAnimInstance()
{
	IsMove = false;
	MoveSpeed = 0.f;

	IsAttack = false;
	AttackIndex = 0;

	IsDeath = false;
}

void UWizardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UWizardAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MoveEnable())
	{
		AWizard* Wizard = Cast<AWizard>(TryGetPawnOwner());
		if (IsValid(Wizard))
		{
			UCharacterMovementComponent* Movement = Wizard->GetCharacterMovement();
			if (IsValid(Movement))
			{
				MoveSpeed = Movement->Velocity.Length() / Movement->MaxWalkSpeed;
			}
		}
	}
}

/*
void UWizardAnimInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWizardAnimInstance, IsMove);
	DOREPLIFETIME(UWizardAnimInstance, IsAttack);
	DOREPLIFETIME(UWizardAnimInstance, IsDeath);
	DOREPLIFETIME(UWizardAnimInstance, AttackIndex);
}
*/

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
