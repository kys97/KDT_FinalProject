// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "WizardAnimInstance.generated.h"


UCLASS()
class FINALPROJECT_API UWizardAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UWizardAnimInstance();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAnimMontage> mNormalAttackMontage;

public:
	bool MoveEnable() 
	{ 
		if (!IsAttack) return true;
		else return false;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	void PlayNormalAttackAnimation();
};
