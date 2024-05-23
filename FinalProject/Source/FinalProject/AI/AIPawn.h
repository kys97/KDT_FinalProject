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

	// SpawnPoint를 통해 생성이 되었을 경우
	// 어떤 SpawnPoint에서 생성이 되었는지를 가지고 있게 한다.
	class AAISpawnPoint* mSpawnPoint;

	// 순찰 PointActor를 저장할 배열
	UPROPERTY(EditAnywhere)
	TArray<class APatrolPointActor*> mPointActorArray;

	// 순찰 PointActor의 위치를 저장할 배열
	TArray<FVector> mPatrolPointArray;

public:
	void SetSpawnPoint(class AAISpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

	void SetPatrolPointArray(const TArray<class APatrolPointActor*>& PatrolPointArray)
	{
		// 받아온 PatrolPoint 배열을 멤버변수로 가지고 있게 한다.
		mPointActorArray = PatrolPointArray;
	}

	float GetHalfHeight() const
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()
	{
		return mCapsule->GetScaledCapsuleRadius();
	}

public:
	virtual void ChangeAIAnimType(uint8 AnimType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 제거될 때 한 번 호출 된다.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
