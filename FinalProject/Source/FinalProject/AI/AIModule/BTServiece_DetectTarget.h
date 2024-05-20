// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "BehaviorTree/BTService.h"
#include "BTServiece_DetectTarget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UBTServiece_DetectTarget : public UBTService
{
	GENERATED_BODY()

public:
	UBTServiece_DetectTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
