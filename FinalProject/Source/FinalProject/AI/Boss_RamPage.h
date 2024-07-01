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
	UPROPERTY(VisibleAnywhere)
	class AFallingSton* mFallingStonEffect;

	TArray<AActor*> SkillActorArray = {};
	TArray<FVector> mRandXYArray = {};

	float mChangeSkillTime = 0.f;
	float mChangeSkillDuration = 10.f;
	bool mSkillEnable = false;

	bool mSpawn = false;
	float mChangeAnimTime = 0.f;

	bool mDestroy = false;
	float mDestroyTime = 0.f;
	float mDestroyDuration = 6.f;

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

	virtual void SetSpawn(bool Value)
	{
		mSpawn = Value;
	}

	virtual void SkillSetting(int32 Num);
	virtual void SkillDestroy(int32 Num);

	void SetHPBar();

protected:
	void SpawnSkill_GroundSmash();
	float RandRangeNumber(float Min, float Max);

	void SpawnSkill_1();
	void SpawnSkill_FireEmit();
	void SpawnSkill_3();
	void SpawnSkill_4();

	void SetDestroyDuration(float Time)
	{
		mDestroyDuration = Time;
		mDestroy = true;
	}

};
