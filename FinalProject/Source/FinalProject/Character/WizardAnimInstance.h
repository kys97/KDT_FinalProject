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
	bool IsDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>> mAttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackIndex;

public:
	bool MoveEnable() 
	{ 
		if (!IsAttack) 
			return true; // 공격 안함
		else 
			return false; // 공격중
	}

	void SetMove(bool move) { IsMove = move; }

	bool AttackEnable()
	{
		return !IsAttack;
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
	void PlayAnimation(const EWizardAttackAnimTypes animType);
	void SetDeath(bool death) { IsDeath = death; }
};
