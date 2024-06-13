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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool IsMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool IsAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool IsDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>> mAttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	int32 AttackIndex;

public:
	bool MoveEnable() { return !IsAttack; }
	bool AttackEnable() { return !IsAttack; }

	void SetMove(bool move) { IsMove = move; }

	int32 GetAttackIndex() { return AttackIndex; }

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	void PlayAnimation(const EWizardAttackAnimTypes animType);
	void SetDeath(bool death) { IsDeath = death; }
};
