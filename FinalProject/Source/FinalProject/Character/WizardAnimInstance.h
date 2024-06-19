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
	float MoveSpeed;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>> mAttackMontageArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackIndex;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsDeath;

public:
	UFUNCTION(BlueprintCallable)
	bool MoveEnable() { return (!IsAttack && !IsDeath); }
	UFUNCTION(BlueprintCallable)
	bool AttackEnable() { return (!IsAttack && !IsDeath); }

	void SetMove(bool move) { IsMove = move; }

	int32 GetAttackIndex() { return AttackIndex; }

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	/*
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	*/
public:
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

public:
	void PlayAnimation(const EWizardAttackAnimTypes animType);
	void SetDeath(bool death) { IsDeath = death; }
};
