// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Components/ActorComponent.h"
#include "AIState.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALPROJECT_API UAIState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIState();

protected:
	UPROPERTY(EditAnywhere)
	FString		mName;
	// 이동 속도
	UPROPERTY(EditAnywhere)
	int32	mMoveSpeed;

	// 상호 작용을 하기 위한 거리
	UPROPERTY(EditAnywhere)
	int32	mInteractionDistance;

public:
	FString	mDataTableRowName;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void ChangeHP(float Event) {}
	virtual FString GetAIName() { return mName; }
	virtual int32 GetAIMoveSpeed() { return mMoveSpeed; }
	virtual int32 GetInteractionDistance() { return mInteractionDistance; }		

	virtual int32 GetAttackPower() { return 0; }
	virtual int32 GetArmorPower() { return 0; }
	virtual	float GetAIHPPercent() { return 0.0f; }

	virtual int32 GetSkill1_Power()	{ return 0;	}
	virtual int32 GetSkill2_Power() { return 0; }
	virtual int32 GetSkill3_Power() { return 0; }
	virtual int32 GetSkill4_Power() { return 0; }
	virtual int32 GetSkill5_Power() { return 0; }
};
