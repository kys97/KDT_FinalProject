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

	float CapsuleRadius = Pawn->GetCapsuleRadius();
	float CapsuleHalfHeight = Pawn->GetHalfHeight();

	FVector AILocation = Pawn->GetActorLocation();

	// 몬스터의 Z위치에서 절반 높이(HalfHeight)를 빼서 발밑 중앙위치 구하기. 
	AILocation.Z -= CapsuleHalfHeight;

	// 주변에 Target이 있는지 판단한다.
	FCollisionQueryParams Param(NAME_None, false, Pawn);

	UAIState* AIState = Pawn->GetState<UAIState>();

	if (!IsValid(AIState))
		return;

	TArray<FHitResult> DetectedArray;	// 충돌 결과
	bool IsDetected = GetWorld()->SweepMultiByChannel(DetectedArray, AILocation, AILocation,
		FQuat::Identity, ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(AIState->mInteractionDistance), Param);

	FHitResult DetectedResult;
	if (IsDetected)
	{
		DetectedResult = DetectedArray[0];
		for (int32 i = 1; i < DetectedArray.Num(); ++i)
		{
			if (DetectedResult.Distance > DetectedArray[i].Distance)
			{
				DetectedResult = DetectedArray[i];
			}
		}
	}

	// 충돌이 됐을 경우 (Target을 찾았을 경우) && 블랙보드에 타겟지정이 안되어 있을 경우
	if (IsDetected && !Pawn->IsSetBlackboardValue())
	{
		// AIController에 지정된 Blackboard에 Target을 저장한다.
		// result.GetActor() : 충돌된 액터를 얻어온다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), DetectedResult.GetActor());
	}

	// 충돌이 안됐을 경우
	if (!IsDetected && !Pawn->IsSetBlackboardValue())
	{
		// AIController에 지정된 Blackboard에 nullptr을 저장한다.
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}


