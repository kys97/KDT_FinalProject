// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "DefaultAIController.h"
#include "AISpawnPoint.h"
#include "PatrolPointActor.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 생성
	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	SetRootComponent(mCapsule);
	mMesh->SetupAttachment(mCapsule);

	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mMovement->SetUpdatedComponent(mCapsule);

	mMovement->MaxSpeed = 700.f;

	// 자동빙의 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ADefaultAIController::StaticClass();

	//// 블루프린트 에셋 가져올 경우 아래 코드 활용
	//static ConstructorHelpers::FClassFinder<AAIController>	AIClass(TEXT(""));
	//if (AIClass.Succeeded())
	//	AIControllerClass = AIClass.Class;

	// 어떤 몬스터는 SpawnPoint 없이 
	// 바로 배치해서 사용할 수 있기 때문에 생성자에서 초기화해주자.
	mSpawnPoint = nullptr;

	// 배치해서 사용할 경우에는 Index가 없어야하기에 -1
	mPatrolIndex = -1;
}

void AAIPawn::SetPatrolPointArray(const TArray<class APatrolPointActor*>& PatrolPointArray)
{
	if (PatrolPointArray.IsEmpty())
		return;

	// 받아온 PatrolPoint 배열을 멤버변수로 가지고 있게 한다.
	mPointActorArray = PatrolPointArray;

	// Spawn시에 생성 위치를 잡아줘서 AIPawn에는 따로 캡슐 절반 위치를 안잡아줬지만
	// 나중에 문제 생긴다면 확인 해보기
	FVector StartPoint = GetActorLocation();

	mPatrolPointArray.Add(StartPoint);

	for (auto Point : mPointActorArray)
	{
		mPatrolPointArray.Add(Point->GetActorLocation());
	}
}

void AAIPawn::ChangeAIAnimType(uint8 AnimType)
{
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	// 0번 인덱스는 AI의 시작 위치이기 때문에
	// 1번 인덱스부터 방문할 수 있게 한다.
	mPatrolIndex = 1;

}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// AIPawn을 생성해준 SpawnPoint가 있을 경우
	// 해당 SpawnPoint의 생성된 오브젝트 정보를 초기화한다.
	if(mSpawnPoint)
		mSpawnPoint->ClearSpawnObject();
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

