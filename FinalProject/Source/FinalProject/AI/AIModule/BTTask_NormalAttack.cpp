// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalAttack.h"
#include "../AIPawn.h"
#include "../DefaultAIController.h"
#include "../MonsterAnimInstance.h"
#include "../MonsterState.h"

UBTTask_NormalAttack::UBTTask_NormalAttack()
{
	NodeName = TEXT("NormalAttack");

	// Tick 함수 호출이 가능하게 한다.
	bNotifyTick = true;

	// OnTaskFinished 이벤트를 사용할 수 있게 한다.
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, 
	uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return EBTNodeResult::Failed;

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject("Target"));

	if (!IsValid(Target))
	{
		// 이동을 멈추게 한다.
		Controller->StopMovement();

		// 애니메이션을 Idle 로 변경한다.
		Pawn->SetActorRotation(Pawn->GetCurrentRotation());
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	if (!Pawn->IsAttackEnable())
	{
		return EBTNodeResult::Failed;
	}

	Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Attack);

	return EBTNodeResult::InProgress;
}

void UBTTask_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	// Controller가 빙의되어 있는 Pawn이 없으면 Task 종료
	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));

	// 타겟이 없어도 Task 종료
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		Pawn->SetActorRotation(Pawn->GetCurrentRotation());
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return;
	}

	if (!Pawn->IsAttackEnable())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	if (Pawn->IsAttackEnd())
	{
		Pawn->SetAttackEnd(false);

		// 타겟과의 거리 체크
		FVector AILocation = Pawn->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();

		// AI가 Target을 바라보는 방향을 구한다.
		FVector	Dir = TargetLocation - AILocation;
		Dir.Z = 0.0;

		FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
		Rot.Pitch = 0.0;
		Rot.Roll = 0.0;

		Pawn->SetActorRotation(Rot);

		// 두 위치 사이의 거리를 구한다.
		AILocation.Z -= Pawn->GetHalfHeight();

		// Target의 RootComponent를 CapsuleComponent로 변환한다.
		UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

		if (IsValid(TargetCapsule))
			TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();

		// FVetor::Distance : 두 위치 사이의 거리를 구한다.
		float Distance = FVector::Distance(AILocation, TargetLocation);

		Distance -= Pawn->GetCapsuleRadius();

		if (IsValid(TargetCapsule))
			Distance -= TargetCapsule->GetScaledCapsuleRadius();

		UMonsterState* MonsterState = Pawn->GetState<UMonsterState>();

		if (!IsValid(MonsterState))
			return;

		// GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("Distance : %f"), Distance));

		// 공격 거리를 빠져나갔을 경우
		if (Distance > MonsterState->GetAIAttackDistance())
		{
			// Task를 종료한다.
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

			// 애니메이션을 Idle 로 변경한다.
			//Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
		}
	}
}


