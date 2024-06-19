// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "BoseAIController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ABoseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABoseAIController();

protected:
	UBehaviorTree* mBehaviorTree;
	UBlackboardData* mBlackboard;

	UPROPERTY(VisibleAnywhere)
	UAIPerceptionComponent* mAIPerception;

	UAISenseConfig_Sight* mSightConfig;

protected:
	virtual void BeginPlay() override;

	// AI에 빙의할 때 함수
	virtual void OnPossess(APawn* InPawn) override;
	// AI에서 빙의 해지 될 때 함수
	virtual void OnUnPossess() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTargetDetect(AActor* Target, FAIStimulus const Stimulus);

public:
	void SetSightConfig();
	void StopAI();
	
};
