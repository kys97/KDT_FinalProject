// Fill out your copyright notice in the Description page of Project Settings.
#include "BTTask_TraceTarget.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../MonsterAnimInstance.h"
#include "../MonsterState.h"

UBTTask_TraceTarget::UBTTask_TraceTarget()
{
	NodeName = TEXT("TraceTarget");

	// Tick 함수 호출 가능 여부
	bNotifyTick = true;

	// OnTaskFinished 이벤트 사용 가능 여부
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_TraceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return EBTNodeResult::Failed;

	// 블랙보드에 있는 Target을 Actor로 얻어온다.
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// 타겟이 없으면 이동을 멈추게 한다.
	if (!IsValid(Target))
	{
		Controller->StopMovement();

		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	mOnGroundLocation = Pawn->GetActorLocation();

	// 타겟을 찾으면 Target을 향해 이동
										// (이동시킬 대상, 목표지점)
	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Run);

	return EBTNodeResult::InProgress;
}

void UBTTask_TraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	// Controller가 빙의되어 있는 Pawn이 없으면 Task 종료
	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		return;
	}

	UPawnMovementComponent* Movement = Pawn->GetMovementComponent();
	if (IsValid(Movement))
	{
		if (!Movement->IsMovingOnGround())
		{
			FVector Location = Pawn->GetActorLocation();
			Pawn->SetActorRelativeLocation(FVector(Location.X, Location.Y, mOnGroundLocation.Z));
		}
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// 타겟이 없어도 Task 종료
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Controller->StopMovement();

		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return;
	}

	UMonsterState* MonsterState = Pawn->GetState<UMonsterState>();

	if (!IsValid(MonsterState))
		return;

	Pawn->SetMoveSpeed((float)MonsterState->mMaxMoveSpeed);

	// 타겟과의 거리 체크
	FVector AILocation = Pawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	FVector	Dir = TargetLocation - AILocation;
	Dir.Z = 0.0;

	FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
	Rot.Pitch = 0.0;
	Rot.Roll = 0.0;

	Pawn->SetActorRotation(Rot);

	AILocation.Z -= Pawn->GetHalfHeight();

	UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(TargetCapsule))
		TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();

	// FVetor::Distance : 두 위치 사이의 거리를 구한다.
	float Distance = FVector::Distance(AILocation, TargetLocation);

	Distance -= Pawn->GetCapsuleRadius();

	if (IsValid(TargetCapsule))
		Distance -= TargetCapsule->GetScaledCapsuleRadius();

	if (Distance < MonsterState->mAttackDistance)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		Controller->StopMovement();

		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
	}
	else if (Distance > MonsterState->mAttackDistance && Pawn->GetMovementComponent()->Velocity == FVector(0))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
	}
}

void UBTTask_TraceTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult); 
}
