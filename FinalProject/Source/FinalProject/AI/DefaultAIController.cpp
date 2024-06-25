// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultAIController.h"

ADefaultAIController::ADefaultAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITree(TEXT(
		"/Script/AIModule.BehaviorTree'/Game/AI/Monster/BT_Default.BT_Default'"));
	
	if (AITree.Succeeded())
		mBehaviorTree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIData(TEXT(
		"/Script/AIModule.BlackboardData'/Game/AI/Monster/BB_Default.BB_Default'"));
	
	if (AIData.Succeeded())
		mBlackboard = AIData.Object;
}

void ADefaultAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// 블랙보드가 있을 경우
	if (mBlackboard)
	{
		// AI 컨트롤러가 가지고 있는 Blackboard 컴포넌트에 읽어온 블랙보드를 지정한다. 
		// 기본적으로 AIController에 Blackboard가 변수로 잡혀있음
		UBlackboardComponent* BlackboardRef = Blackboard;

		// 읽어온 블랙보드 지정
		if (UseBlackboard(mBlackboard, BlackboardRef))
		{
			// 블랙보드 지정이 성공했을 경우 비헤이비어트리 동작
			RunBehaviorTree(mBehaviorTree);
		}
	}
}

void ADefaultAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ADefaultAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (IsValid(BehaviorTreeComponent))
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
