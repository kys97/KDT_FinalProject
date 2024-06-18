// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

UENUM(BlueprintType)
enum class EMonsterAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Sleep,
	Attack,
	TakeDamage,
	Death
};

UCLASS()
class FINALPROJECT_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double mPlayerMoveSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	EMonsterAnimType mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool mLoopAnimation = false;

public:
	void ChangeAnimType(EMonsterAnimType Type)
	{
		mAnimType = Type;
	}

	void ChangeAnimLoop(bool Loop)
	{
		mLoopAnimation = Loop;
	}

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_HitReactStart();

	UFUNCTION()
	void AnimNotify_HitReactEnd();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
};
