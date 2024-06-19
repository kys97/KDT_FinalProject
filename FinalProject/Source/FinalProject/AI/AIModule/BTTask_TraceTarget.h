// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TraceTarget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UBTTask_TraceTarget : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TraceTarget();

protected:
	FVector mOnGroundLocation;
	float mAccTime = 0.f;
	float mStunDuration = 5.f;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult);
	
	void SetStopTask(UBehaviorTreeComponent& OwnerComp, AAIController* Controller);

	void SetDirection(AActor* AIPawn, FVector& AILocation, FVector& TargetLocation);
	float GetDistance(AActor* AIPawn, AActor* Target, FVector& AILocation, FVector& TargetLocation);
};
