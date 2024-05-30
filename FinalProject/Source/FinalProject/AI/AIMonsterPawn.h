// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "AIMonsterPawn.generated.h"


// FTableRowBase 구조체를 상속 받아서 만들어야
// 데이터테이블에서 사용할 수 있는 구조체가 된다. 
USTRUCT(BlueprintType)
struct FMonsterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	// 공격력
	UPROPERTY(EditAnywhere)
	int32	mAttackPower;
	// 방어력
	UPROPERTY(EditAnywhere)
	int32	mArmorPower;

	UPROPERTY(EditAnywhere)
	int32	mHPMax;

	UPROPERTY(EditAnywhere)
	int32	mMPMax;
	// 최대 이동 속도
	UPROPERTY(EditAnywhere)
	int32	mMaxMoveSpeed;
	// 이동 속도
	UPROPERTY(EditAnywhere)
	int32	mMoveSpeed;
	// 공격 거리
	UPROPERTY(EditAnywhere)
	int32	mAttackDistance;
	// 타겟 감지 거리
	UPROPERTY(EditAnywhere)
	int32	mDetectDistance;
};

UCLASS()
class FINALPROJECT_API AAIMonsterPawn : public AAIPawn
{
	GENERATED_BODY()

protected:
	static UDataTable* mMonsterDataTable;

public:
	static const FMonsterData* FindMonsterData(const FString& Name);

public:
	AAIMonsterPawn();

protected:
	class UMonsterAnimInstance* mAnimInst;
	FString mTableRowName;

	class UMonsterState* mMonsterState;

	bool mOverlap;
	bool mAttackEnd;

	bool mDeathEnd;
	float mDeadTime;

	UPROPERTY(EditAnywhere)
	float mDeadDuration;

public:
	void DeathEnd();

	virtual void ChangeAIAnimType(uint8 AnimType);

	virtual bool AIIsOverlap()
	{
		return mOverlap;
	}

	virtual void ChangeOverlapVlaue(bool Value)
	{
		mOverlap = Value;
	}

	virtual void NormalAttack();

	virtual void SetAttackEnd(bool End)
	{
		mAttackEnd = End;
	}

	virtual bool IsAttackEnd()
	{
		return mAttackEnd;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

