// Fill out your copyright notice in the Description page of Project Settings.


#include "Storm.h"
#include "TimerManager.h"


// Sets default values
AStorm::AStorm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Storm Particle Set
	static ConstructorHelpers::FObjectFinder<UParticleSystem> StormParticle{ TEXT("/Script/Engine.ParticleSystem'/Game/Blueprint/FXV/P_ky_aquaStorm.P_ky_aquaStorm'") };
	if (StormParticle.Succeeded())
	{
		mParticle->SetTemplate(StormParticle.Object);
	}

	// OutSide Collision Set
	mOutSideCollision->SetCapsuleSize(200.f, 420.f);
	mOutSideCollision->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	// mOutSideCollision->Deactivate();

	// InSide Collision Set
	mInsideCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InsideCollision"));
	mInsideCollision->SetupAttachment(GetRootComponent());
	mInsideCollision->SetCapsuleSize(90.f, 370.f);
	mInsideCollision->SetRelativeLocation(FVector(0.f, 0.f, 270.f));
	mInsideCollision->SetCollisionProfileName(TEXT("Skill"));
	mInsideCollision->CanCharacterStepUpOn = ECB_No;
	// mInsideCollision->Deactivate();

	// Enable Set
	GetRootComponent()->bAutoActivate = false;

	// Var Set
	mScale = 0.2f;
	mFadeSpeed = 0.5f;
	mMoveSpeed = 500.f;
	IsMove = false;
}

// Called when the game starts or when spawned
void AStorm::BeginPlay()
{
	Super::BeginPlay();
	
	// Delay
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AStorm::BeginDelayOver, 1.0f, false);
}

void AStorm::BeginDelayOver()
{
	// Scale Init
	mParticle->SetRelativeScale3D(FVector(1, 1, 1) * mScale);

	// Activate
	mParticle->Activate();
}


// Called every frame
void AStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mParticle->IsActive())
	{
		if (mScale < 1) // Scale
		{
			mScale += mFadeSpeed * DeltaTime;
			mParticle->SetRelativeScale3D(FVector(1, 1, 1) * mScale);
		}
		else if (!IsMove)
		{
			IsMove = true;

			// Delay
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AStorm::SkillDelayOver, 3.0f, false);
		}
		else // Move
		{
			SetActorRelativeLocation(GetActorLocation() + (mMoveDir * mMoveSpeed * DeltaTime));
		}
	}
}

void AStorm::SkillDelayOver()
{
	mParticle->Deactivate();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AStorm::DestoyStorm, 2.0f, false);
}

void AStorm::DestoyStorm()
{
	Destroy();
}
