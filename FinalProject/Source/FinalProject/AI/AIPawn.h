// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

UCLASS()
class FINALPROJECT_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* mMovement;

	UPROPERTY(EditAnywhere)
	class UAIState* mState;

	// SpawnPoint를 통해 생성이 되었을 경우
	// 어떤 SpawnPoint에서 생성이 되었는지를 가지고 있게 한다.
	class AAISpawnPoint* mSpawnPoint;

	// 순찰 PointActor를 저장할 배열
	UPROPERTY(EditAnywhere)
	TArray<class APatrolPointActor*> mPointActorArray;

	// 순찰 PointActor의 위치를 저장할 배열
	TArray<FVector> mPatrolPointArray;

	// 방문할 순찰 위치를 꺼내오기 위한 Index
	int32 mPatrolIndex;
	// 순찰 방향
	int32 mPatrolDir;

public:
	virtual FRotator GetCurrentRotation();

	virtual void SetMoveSpeed(float Speed);

	template <typename T>
	T* GetState()
	{
		return Cast<T>(mState);
	}

	void NextPatrolPointIndex()
	{
		mPatrolIndex += mPatrolDir;

		// 배열의 인덱스 범위를 벗어났는지 판단
		if (mPatrolIndex >= mPatrolPointArray.Num())	// Num() : 배열에 엘리먼트가 몇 개인지 확인
		{
			// 방향을 역방향으로 바꿔준다.
			mPatrolDir = -1;
			mPatrolIndex -= 2;
		}
		else if (mPatrolIndex < 0)
		{
			// 방향을 정방향으로 바꿔준다.
			mPatrolDir = 1;
			mPatrolIndex = 1;
		}
	}
	FVector GetPatrolPoint()
	{
		// mPatrolIndex 번지에 있는 값 반환
		return mPatrolPointArray[mPatrolIndex];
	}

	void SetSpawnPoint(class AAISpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

	// PointActor배열 세팅
	void SetPointActorArray(const TArray<class APatrolPointActor*>& PatrolPointArray);

	// 순찰 위치 배열이 비어있는지 확인
	bool IsPatrolPointEmpty()
	{
		return mPatrolPointArray.IsEmpty();
	}

	float GetHalfHeight() const
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()
	{
		return mCapsule->GetScaledCapsuleRadius();
	}

	virtual void SetAttackEnd(bool End);
	virtual bool IsAttackEnd();

	virtual void SetAttackEnable(bool End);
	virtual bool IsAttackEnable();

	virtual void SetStunState(bool Stun);
	virtual bool IsStun();

public:
	virtual void ChangeAIAnimType(uint8 AnimType);
	virtual uint8 GetAnimType();
	virtual bool AIIsOverlap();
	virtual void ChangeOverlapVlaue(bool Value);

	virtual bool IsSetBlackboardValue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 제거될 때 한 번 호출 된다.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	virtual void OnConstruction(const FTransform& Transform);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

};
