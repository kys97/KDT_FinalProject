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

	if(AnimType == EWizardAnimType::Idle)
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Red, FString::Printf(TEXT("Idle")));
	else if(AnimType == EWizardAnimType::Move)
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Blue, FString::Printf(TEXT("Move")));

	AWizard* Character = Cast<AWizard>(TryGetPawnOwner());

	if (IsValid(Character))
	{
		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();
		if (IsValid(Movement))
		{
			if (Movement->Velocity.Length() > 0.0f)
				AnimType = EWizardAnimType::Move;
			else if(AnimType == EWizardAnimType::Move)
				AnimType = EWizardAnimType::Idle;
		}
	}
}

void UWizardAnimInstance::PlayNormalAttackAnimation()
{
	AnimType = EWizardAnimType::NormalAttack;
	if( AnimType == EWizardAnimType::NormalAttack)
		GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Cyan, FString::Printf(TEXT("NormalAttack")));

	// 공격 애니메이션 끝나고 IDle로 돌아가는거
}
