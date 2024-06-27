// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIMonsterPawn.h"
#include "Boss_RamPage.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ABoss_RamPage : public AAIMonsterPawn
{
	GENERATED_BODY()

public:
	ABoss_RamPage();

protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mBodyCapsule;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mLeftArm;
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mRightArm;

	UMonsterState* mMonsterState;

	UPROPERTY(VisibleAnywhere)
	class AEffect_FireEmit* mEmitEffect;

	AActor* SkillActor = nullptr;

	int32 ChangeAnimCnt = 0.f;
	int32 ChangeAnimMaxCnt = 2.f;
	bool SkillEnable = false;

protected:
	void SetCapsuleCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void AttackOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual EMonsterType GetMonsterType()
	{
		return mMonsterType;
	}

	virtual void SkillSetting(int32 Num);
	virtual void SkillDestroy()
	{
		if (SkillActor != nullptr)
			SkillActor->Destroy();
	}

	void SetHPBar();
};
