// Fill out your copyright notice in the Description page of Project Settings.


#include "Thunder.h"


AThunder::AThunder()
{
	PrimaryActorTick.bCanEverTick = true;

	// Thunder Particle Set
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ThunderParticle{ TEXT("/Script/Engine.ParticleSystem'/Game/Blueprint/FXV/P_ky_lightning3.P_ky_lightning3'") };
	if (ThunderParticle.Succeeded())
	{
		mParticle->SetTemplate(ThunderParticle.Object);
	}
	mParticle->SetRelativeScale3D(FVector(2, 2, 2));

	// OutSide Collision Set
	mOutSideCollision->SetCapsuleSize(180.f, 350.f);
	mOutSideCollision->SetRelativeLocation(FVector(0.f, 0.f, 165.f));
	mOutSideCollision->OnComponentBeginOverlap.AddDynamic(this, &AThunder::OnCapsuleOverlapBegin);

	// Enable Set
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetRootComponent()->bAutoActivate = false;
}

void AThunder::BeginPlay()
{
	Super::BeginPlay();

	// Delay
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AThunder::SkillBegin, 0.5f, false);
}

void AThunder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AThunder::OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAIMonsterPawn* Monster = Cast<AAIMonsterPawn>(OtherActor);
	if (OtherActor && SkillOwner && (OtherActor != SkillOwner) && Monster)
	{
		// Monster->TakeDamage()
		FDamageEvent DmgEvent;
		Monster->TakeDamage(SkillDamage, DmgEvent, SkillOwner->GetController(), SkillOwner);
	}
}


void AThunder::SkillBegin()
{
	// Activate
	mParticle->Activate();
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	// Delay
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AThunder::SkillOver, 1.0f, false);
}

void AThunder::SkillOver()
{
	mParticle->Deactivate();
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}

