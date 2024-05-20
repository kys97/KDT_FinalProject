// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "DefaultAIController.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ADefaultAIController : public AAIController
{
	GENERATED_BODY()

public:
	ADefaultAIController();

protected:
	UBehaviorTree* mBehaviorTree;
	UBlackboardData* mBlackboard;
	
protected:
	// AI에 빙의할 때 함수
	virtual void OnPossess(APawn* InPawn) override;
	// AI에서 빙의 해지 될 때 함수
	virtual void OnUnPossess() override;

};
