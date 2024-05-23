// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");

	bNotifyTick = true;

	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return EBTNodeResult::Failed;

	// 순찰 지점 배열이 비어있는 경우는
	// 방문할 위치가 없기 때문에 Task 종료
	if (Pawn->IsPatrolPointEmpty())
		return EBTNodeResult::Failed;

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	if (IsValid(Target))
	{
		Controller->StopMovement();

		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::Type();
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

}
