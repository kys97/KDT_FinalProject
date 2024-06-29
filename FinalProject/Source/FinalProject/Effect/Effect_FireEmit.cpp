// Fill out your copyright notice in the Description page of Project Settings.


#include "Effect_FireEmit.h"

AEffect_FireEmit::AEffect_FireEmit()
{ 	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle{ TEXT("/Script/Engine.ParticleSystem'/Game/AI/Asset/Particle/P_Flamethrower.P_Flamethrower'") };
	if (Particle.Succeeded())
	{
		mParticle->SetTemplate(Particle.Object);
	}
	
	mCapsule->SetCollisionProfileName(TEXT("BossSkill"));
	mCapsule->SetRelativeLocation(FVector(0.f, 500.f, 0.f));
	mCapsule->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));
	mCapsule->SetCapsuleHalfHeight(500);
	mCapsule->SetCapsuleRadius(300);

	mParticle->SetRelativeLocation(FVector(0.f, 0.f, -500.f));
	//mParticle->SetRelativeRotation(FRotator(180.f, 0.f, 0.f));
	mParticle->SetRelativeScale3D(FVector(2.0f, 1.0f, 1.0f));
}

void AEffect_FireEmit::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("AEffect_FireEmit BeginPlay"));

	mIsOverlap = true;
	mAttackTime = 0.f;
	OverlapActor = nullptr;

	mCapsule->OnComponentBeginOverlap.AddDynamic(this, &AEffect_FireEmit::BeginOverlap);
}

void AEffect_FireEmit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mIsOverlap)
	{
		mAttackTime += DeltaTime;
		if (mAttackTime > mAttackDuration)
		{
			FDamageEvent DmgEvent;
			OverlapActor->TakeDamage(mSkillPower, DmgEvent, GetInstigatorController(), this);
		
			mAttackTime = 0.f;
		}
	}
}

void AEffect_FireEmit::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("AEffect_FireEmit Overlap"));

	mIsOverlap = true;
	mAttackTime = 0.f;
	OverlapActor = OtherActor;

	FDamageEvent DmgEvent;
	OverlapActor->TakeDamage(mSkillPower, DmgEvent, GetInstigatorController(), this);
}

void AEffect_FireEmit::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mIsOverlap = false;
	mAttackTime = 0.f;
	OverlapActor = nullptr;
}