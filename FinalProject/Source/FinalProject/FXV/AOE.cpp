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
	// mOutSideCollision->SetCapsuleSize(180.f, 350.f);
	// mOutSideCollision->SetRelativeLocation(FVector(0.f, 0.f, 165.f));
	// mOutSideCollision->OnComponentBeginOverlap.AddDynamic(this, &AAOE::OnCapsuleOverlapBegin);

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
}

void AAOE::OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AAOE::SkillBegin()
{
}

void AAOE::SkillOver()
{
}

void AAOE::Initialize(AWizard* owner, int32 damage, EWizardJob job)
{
}
