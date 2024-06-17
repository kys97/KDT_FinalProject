// Fill out your copyright notice in the Description page of Project Settings.


#include "AOE.h"

AAOE::AAOE()
{
	PrimaryActorTick.bCanEverTick = true;

	// AOE Particle Set
	static ConstructorHelpers::FObjectFinder<UParticleSystem> AOEParticle{ TEXT("/Script/Engine.ParticleSystem'/Game/Blueprint/FXV/HealAura.HealAura'") };
	if (AOEParticle.Succeeded())
	{
		mParticle->SetTemplate(AOEParticle.Object);
	}
	mParticle->SetRelativeScale3D(FVector(2, 2, 2));

	// OutSide Collision Set
	mOutSideCollision->SetCapsuleSize(110.f, 180.f);
	mOutSideCollision->SetRelativeLocation(FVector(0.f, 0.f, 70.f));
	mOutSideCollision->OnComponentBeginOverlap.AddDynamic(this, &AAOE::OnCapsuleOverlapBegin);
	mOutSideCollision->OnComponentEndOverlap.AddDynamic(this, &AAOE::OnCapsuleOverlapEnd);
	// mOutSideCollision->SetCollisionProfileName(TEXT("Defense"));

	// Enable Set
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetRootComponent()->bAutoActivate = false;
}

void AAOE::BeginPlay()
{
	Super::BeginPlay();
}

void AAOE::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mParticle->IsActive() && SkillOwner)
	{
		SkillOwner->HealHP(DeltaTime);
	}
}

void AAOE::OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AWizard* Player = Cast<AWizard>(OtherActor);
	if (Player) 
	{
		// [Network] TODO : Add Player to Heal List
	}
}

void AAOE::OnCapsuleOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWizard* Player = Cast<AWizard>(OtherActor);
	if (Player)
	{
		// [Network] TODO : Delete Player to Heal List
	}
}

void AAOE::Initialize(AWizard* owner, int32 damage, EWizardJob job)
{
	SkillOwner = owner;
	SkillDamage = damage;
	Job = job;
	
	SkillOwner->OnInvincibility();

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAOE::SkillBegin, 1.5f, false);
}

void AAOE::SkillBegin()
{
	// Skill Color Set
	/*
	switch (Job)
	{
	case EWizardJob::Blue:
		Color = FVector(0.0f, 3.0f, 8.0f);
		break;
	}
	mParticle->SetVectorParameter(TEXT("color"), Color);
	*/

	// Activate
	mParticle->Activate();
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// SkillOver
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAOE::SkillOver, 3.5f, false);
}

void AAOE::SkillOver()
{
	mParticle->Deactivate();
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SkillOwner->OffInvincibility();

	// Destroy
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAOE::SkillDestroy, 1.0f, false);
}

void AAOE::SkillDestroy()
{
	Destroy();
}
