// Fill out your copyright notice in the Description page of Project Settings.


#include "BoseAIController.h"

ABoseAIController::ABoseAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> AITree(TEXT(
		"/Script/AIModule.BehaviorTree'/Game/AI/Monster/BT_Bose.BT_Bose'"));

	if (AITree.Succeeded())
		mBehaviorTree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData> AIData(TEXT(
		"/Script/AIModule.BlackboardData'/Game/AI/Monster/BB_Default.BB_Default'"));

	if (AIData.Succeeded())
		mBlackboard = AIData.Object;

	mAIPerception = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");

	// AIPerception 등록
	SetPerceptionComponent(*mAIPerception);
	SetSightConfig();
	// AIPerception에 Sight 등록
	mAIPerception->ConfigureSense(*mSightConfig);

	// 대표 감각 설정
	mAIPerception->SetDominantSense(mSightConfig->GetSenseImplementation());
}

void ABoseAIController::BeginPlay()
{
	Super::BeginPlay();

	mAIPerception->OnTargetPerceptionUpdated.AddDynamic(
		this, &ABoseAIController::OnTargetDetect);
}

void ABoseAIController::OnPossess(APawn* InPawn)
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

void ABoseAIController::OnUnPossess()
{
	Super::OnUnPossess();
}

void ABoseAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABoseAIController::OnTargetDetect(AActor* Target, FAIStimulus const Stimulus)
{
	UE_LOG(Network, Warning, TEXT("Target Detect"));

	// 감지가 성공적이면
	if (Stimulus.WasSuccessfullySensed())
	{
		AController* Controller = Cast<AController>(Target);

		if (IsValid(Controller))
			Target = Controller->GetPawn();

		if (Target != Blackboard->GetValueAsObject(TEXT("Target")))
		{
			Blackboard->SetValueAsObject(TEXT("Target"), Target);
		}
	}

	else
	{
		Blackboard->SetValueAsObject(TEXT("Target"), nullptr);
	}
}

void ABoseAIController::SetSightConfig()
{
	// 시야 감지 추가
	mSightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

	// 시야 반경
	mSightConfig->SightRadius = 700.f;
	// 시야를 읽기 시작하는 부분
	mSightConfig->LoseSightRadius = mSightConfig->SightRadius + 150.f;
	// 시야 각도
	mSightConfig->PeripheralVisionAngleDegrees = 90.f;
	// 기본적으로 마지막으로 감지된 객체가 범위 내에 있으면 항상 자동으로 볼 수 있게 세팅
	mSightConfig->AutoSuccessRangeFromLastSeenLocation = -1.f;
	// 감지할 수 있는 시간 - 0은 항상 감지
	mSightConfig->SetMaxAge(0.f);

	mSightConfig->DetectionByAffiliation.bDetectEnemies = true;
	mSightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	mSightConfig->DetectionByAffiliation.bDetectNeutrals = true;
}

void ABoseAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (IsValid(BehaviorTreeComponent))
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
