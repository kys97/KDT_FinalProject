// Fill out your copyright notice in the Description page of Project Settings.


#include "BTServiece_DetectTarget.h"
#include "../DefaultAIController.h"
#include "../AIPawn.h"
#include "../AIState.h"

UBTServiece_DetectTarget::UBTServiece_DetectTarget()
{
	NodeName = TEXT("DetectTarget");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTServiece_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// 이 Serviec를 사용하고 있는 AIController 를 얻어온다. 
	AAIController* Controller = OwnerComp.GetAIOwner();

	// 얻어온 AIController가 빙의되어 있는 Pawn을 얻어온다. 
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());

	if (!IsValid(Pawn))
		return;

	FVector AILocation = Pawn->GetActorLocation();

	// 몬스터의 Z위치에서 절반 높이(HalfHeight)를 빼서 발밑 중앙위치 구하기. 
	AILocation.Z -= Pawn->GetHalfHeight();

	// 주변에 Target이 있는지 판단한다.
	FCollisionQueryParams Param(NAME_None, false, Pawn);

	UAIState* AIState = Pawn->GetState<UAIState>();

	if (!IsValid(AIState))
		return;

	FHitResult result;	// 충돌 결과
	bool IsCollision = GetWorld()->SweepSingleByChannel(result, AILocation, AILocation, 
		FQuat::Identity, ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AIState->mInteractionDistance), Param);

#if ENABLE_DRAW_DEBUG

	FColor DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), AILocation,
		AIState->mInteractionDistance, 20, DrawColor, false, 0.35f);

#endif

	// 충돌이 됐을 경우 (Target을 찾았을 경우)
	if (IsCollision)
	{
		// AIController에 지정된 Blackboard에 Target을 저장한다.
		// result.GetActor() : 충돌된 액터를 얻어온다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}

	// 충돌이 안됐을 경우
	if (!IsCollision)
	{
		// AIController에 지정된 Blackboard에 nullptr을 저장한다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}


