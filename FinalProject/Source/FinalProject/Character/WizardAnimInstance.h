// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "WizardAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EWizardAnimType : uint8
{
	Idle,
	Move,
	NormalAttack,
	Death
};

UCLASS()
class FINALPROJECT_API UWizardAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UWizardAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	EWizardAnimType	AnimType;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void PlayNormalAttackAnimation();
};
