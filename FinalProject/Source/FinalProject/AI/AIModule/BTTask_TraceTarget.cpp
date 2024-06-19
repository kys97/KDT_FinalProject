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

		Pawn->SetActorRotation(Pawn->GetCurrentRotation());
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	UMonsterState* MonsterState = Pawn->GetState<UMonsterState>();

	if (!IsValid(MonsterState))
		return EBTNodeResult::Failed;

	mOnGroundLocation = Pawn->GetActorLocation();

	if (Pawn->IsAttackEnable())
	{
		if (Pawn->IsStun())
		{
			Pawn->SetMoveSpeed((float)MonsterState->mMoveSpeed);
		}
		else {
			Pawn->SetMoveSpeed((float)MonsterState->mMaxMoveSpeed);
		}
		Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Run);

		// 타겟을 찾으면 Target을 향해 이동
											// (이동시킬 대상, 목표지점)
		UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
	}

	return EBTNodeResult::InProgress;
}

void UBTTask_TraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();

	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	UMonsterState* MonsterState = Pawn->GetState<UMonsterState>();
	UPawnMovementComponent* Movement = Pawn->GetMovementComponent();
	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	{
		// Controller가 빙의되어 있는 Pawn이 없으면 Task 종료
		if (!IsValid(Pawn))
		{
			SetStopTask(OwnerComp, Controller);
			return;
		}

		if (!IsValid(MonsterState))
		{
			SetStopTask(OwnerComp, Controller);
			return;
		}

		if (IsValid(Movement))
		{
			if (!Movement->IsMovingOnGround())
			{
				FVector Location = Pawn->GetActorLocation();
				Pawn->SetActorRelativeLocation(FVector(Location.X, Location.Y, mOnGroundLocation.Z));
			}
		}

		// 타겟이 없어도 Task 종료
		if (!IsValid(Target))
		{
			SetStopTask(OwnerComp, Controller);

			Pawn->SetActorRotation(Pawn->GetCurrentRotation());
			Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);

			return;
		}
		else if (Pawn->GetAnimType() == (uint8)EMonsterAnimType::Idle)
		{
			Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Run);
		}
	}

	if (!Pawn->IsAttackEnable())
	{
		if(Pawn->GetMovementComponent()->Velocity.Size() <= 0.f)
		{
			Controller->StopMovement();
		}
	}
	if (Pawn->IsAttackEnable())
	{
		if (Pawn->GetAnimType() == (uint8)EMonsterAnimType::Run
			&& (Pawn->GetMovementComponent()->Velocity.Size() <= 0.f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
		}
		else if (Pawn->GetAnimType() != (uint8)EMonsterAnimType::Run
			&& (Pawn->GetMovementComponent()->Velocity.Size() > 0.f))
		{
			Controller->StopMovement();
		}

		FVector AILocation = Pawn->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();

		SetDirection(Pawn, AILocation, TargetLocation);

		if (Pawn->IsStun())
		{
			mAccTime += DeltaSeconds;

			Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Run);;
			Pawn->SetMoveSpeed((float)MonsterState->mMoveSpeed);
			UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);

			if (mAccTime >= mStunDuration)
			{
				Pawn->SetMoveSpeed((float)MonsterState->mMaxMoveSpeed);

				Pawn->SetStunState(false);

				mAccTime = 0.f;
			}
		}

		float Distance = GetDistance(Pawn, Target, AILocation, TargetLocation);

		if (Distance <= MonsterState->mAttackDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

			Controller->StopMovement();

			Pawn->ChangeAIAnimType((uint8)EMonsterAnimType::Idle);
		}
	}
}

void UBTTask_TraceTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult); 
}


void UBTTask_TraceTarget::SetStopTask(UBehaviorTreeComponent& OwnerComp,
	AAIController* Controller)
{
	FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

	Controller->StopMovement();
}

void UBTTask_TraceTarget::SetDirection(AActor* AIPawn, FVector& AILocation, FVector& TargetLocation)
{
	// 속도 벡터를 가져와서 방향을 구한다.
	// 방향은 x, y의 값을 이용해서 방향을 구한다.

	AAIPawn* Pawn = Cast<AAIPawn>(AIPawn);

	FVector	Dir;
	if (Pawn->GetMovementComponent()->Velocity == FVector(0))
	{
		Dir = TargetLocation - AILocation;
	}
	else {
		Dir = Pawn->GetMovementComponent()->Velocity;
	}
	Dir.Z = 0.f;

	// 벡터 정규화
	Dir.Normalize();

	FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
	Rot.Pitch = 0.0;
	Rot.Roll = 0.0;

	Pawn->SetActorRotation(Rot);
}

float UBTTask_TraceTarget::GetDistance(AActor* AIPawn, AActor* Target, FVector& AILocation, FVector& TargetLocation)
{
	AAIPawn* Pawn = Cast<AAIPawn>(AIPawn);

	// 타겟과의 거리 체크
	AILocation.Z -= Pawn->GetHalfHeight();

	UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());

	if (IsValid(TargetCapsule))
		TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();

	// FVetor::Distance : 두 위치 사이의 거리를 구한다.
	float Distance = FVector::Distance(AILocation, TargetLocation);

	Distance -= Pawn->GetCapsuleRadius();

	if (IsValid(TargetCapsule))
		Distance -= TargetCapsule->GetScaledCapsuleRadius();

	return Distance;
}
