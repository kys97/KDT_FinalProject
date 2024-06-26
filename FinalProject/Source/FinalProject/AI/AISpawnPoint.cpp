// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"
#include "AIPawn.h"

// Sets default values
AAISpawnPoint::AAISpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	mTrigger->SetupAttachment(mRoot);

	mTrigger->SetBoxExtent(FVector(30.0, 30.0, 100.0));
	mTrigger->SetRelativeLocation(FVector(0.0, 0.0, 100.0));

	mTrigger->SetCollisionProfileName(TEXT("MonsterTrigger"));

#if WITH_EDITORONLY_DATA

	mArror = CreateDefaultSubobject<UArrowComponent>(TEXT("Arror"));
	mArror->SetupAttachment(mRoot);

	mArror->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	mArror->bVisualizeComponent = true;

	mRoot->bVisualizeComponent = true;

#endif // WITH_EDITORONLY_DATA

	mSpawnAI = nullptr;
	mAccTime = 0.f;
	mSpawnTime = 0.f;
}

// Called when the game starts or when spawned
void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
		Spawn();
}

// Called every frame
void AAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Yellow, TEXT("Log! AAISpawnPoint/Tick"));
	//UE_LOG(Network, Warning, TEXT("Log! AAISpawnPoint/Tick"));

	if (HasAuthority())
	{
		// 생성된 오브젝트가 nullptr 일 경우에는
		// 해당 오브젝트는 제거가 되었다는 뜻이므로 새로 생성해주자.
		if (!mSpawnAI)
		{
			mAccTime += DeltaTime;

			if (mAccTime >= mSpawnTime)
				Spawn();
		}
	}
}

void AAISpawnPoint::Spawn()
{
	if (!IsValid(mSpawnClass))
		return;

	UE_LOG(Network, Warning, TEXT("Server Log! AAISpawnPoint/Spawn"));

	FActorSpawnParameters SpawnParam;

	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// 생성하고자 하는 클래스의 Default Object를 가져온다.
	AAIPawn* DefaultObj = Cast<AAIPawn>(mSpawnClass->GetDefaultObject());

	float HalfHeight = 0.f;

	// 생성 되는 Pawn의 위치는 SpawnPoint의 현재 위치로부터 캡슐의 절반 크기만큼
	// 위로 이동시킨 위치에 스폰된다.
	if (IsValid(DefaultObj))
		HalfHeight = DefaultObj->GetHalfHeight();

	float RandYaw;
	if (mMonsterType == EAIMonsterType::Nomal)
	{
		RandYaw = FMath::FRandRange(-180.f, 180.f);
		mSpawnAI = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass,
			GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight), FRotator(0.f, RandYaw, 0.f), SpawnParam);
	}
	else
	{
		mSpawnAI = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass,
			GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight), FRotator::ZeroRotator, SpawnParam);
	}
	// 생성된 스폰 포인트를 지정해준다.
	mSpawnAI->SetSpawnPoint(this);

	mSpawnAI->SetPointActorArray(mPointActorArray);
}

void AAISpawnPoint::ClearSpawnObject()
{
	mSpawnAI = nullptr;
	mAccTime = 0.f;
}

