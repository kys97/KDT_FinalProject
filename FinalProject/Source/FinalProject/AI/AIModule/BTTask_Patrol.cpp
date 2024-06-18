// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"
#include "../MonsterState.h"

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

		Pawn->SetActorRotation(Pawn->GetCurrentRotation());
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	// 방문할 위치
	FVector MovePoint = Pawn->GetPatrolPoint();

	// 방문할 위치로 이동
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, MovePoint);

	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Walk);

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		return;
	}

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// Patrol은 비 전투시에 동작하기 때문에
	// Target이 있으면 전투 상태가 되므로 Task 종료 
	if (IsValid(Target))
	{
		// 타겟이 있으면 이동을 멈추고
		Controller->StopMovement();

		Pawn->SetActorRotation(Pawn->GetCurrentRotation());
		// 애니메이션을 Idle로 변경하고
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		// Task 종료
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	UMonsterState* MonsterState = Pawn->GetState<UMonsterState>();

	if (!IsValid(MonsterState))
		return;

	Pawn->SetMoveSpeed((float)MonsterState->mMoveSpeed);
	
	// 속도 벡터를 가져와서 방향을 구한다.
	// 방향은 x, y의 값을 이용해서 방향을 구한다.
	FVector	Dir = Pawn->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;

	Dir.Normalize();

	Pawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

	// Overlap 결과로 도착 확인
	bool Overlap = Pawn->AIIsOverlap();

	if (Overlap)
	{
		// Task 종료
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		// 타겟이 있으면 이동을 멈추고
		Controller->StopMovement();

		Pawn->SetActorRotation(Pawn->GetCurrentRotation());
		// 애니메이션을 Idle로 변경하고
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		// 패트롤 인덱스를 구해준다.
		Pawn->NextPatrolPointIndex();

		Pawn->ChangeOverlapVlaue(false);
	}

	// -----------------타겟 간의 거리를 이용한 Task 관리-------------------
	
	//FVector AILocation = Pawn->GetActorLocation();
	//AILocation.Z -= Pawn->GetHalfHeight();

	//// 방문할 위치
	//FVector GoalLocation = Pawn->GetPatrolPoint();

	//// 타겟과의 거리를 체크
	//float Distance = FVector::Distance(AILocation, GoalLocation);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Distance : %f"), Distance));

	//if (Distance <= 120.f)
	//{
	//	// Task 종료
	//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

	//	// 타겟이 있으면 이동을 멈추고
	//	Controller->StopMovement();

	//	// 애니메이션을 Idle로 변경하고
	//	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
	//}
}
