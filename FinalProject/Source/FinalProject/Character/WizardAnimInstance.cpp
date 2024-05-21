// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAnimInstance.h"
#include "Wizard.h"

UWizardAnimInstance::UWizardAnimInstance()
{
	AnimType = EWizardAnimType::Idle;
}

void UWizardAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UWizardAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AWizard* Character = Cast<AWizard>(TryGetPawnOwner());

	if (IsValid(Character))
	{
		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
		if (IsValid(Movement))
		{
			if (Movement->Velocity.Length() > 0.0f)
				AnimType = EWizardAnimType::Move;
			else
				AnimType = EWizardAnimType::Idle;
		}
	}
}
