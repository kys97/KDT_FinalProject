// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"
#include "DefaultAIController.h"

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

	// 자동빙의 설정
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIControllerClass = ADefaultAIController::StaticClass();

	//// 블루프린트 에셋 가져올 경우 아래 코드 활용
	//static ConstructorHelpers::FClassFinder<AAIController>	AIClass(TEXT(""));
	//if (AIClass.Succeeded())
	//	AIControllerClass = AIClass.Class;
}

void AAIPawn::ChangeAIAnimType(uint8 AnimType)
{
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
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

