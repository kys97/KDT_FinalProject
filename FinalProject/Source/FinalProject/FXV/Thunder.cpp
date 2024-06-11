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
	
	// mParticle->OnParticleDeath.AddDynamic(this, &AThunder::OnSkillOver);
	// mParticle->OnParticleCollide.AddDynamic(this, &AThunder::OnSkillCollide);

	// Enable Set
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetRootComponent()->bAutoActivate = false;
}

void AThunder::BeginPlay()
{
	Super::BeginPlay();
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
		if (SkillOwner->HasAuthority())
		{
			Monster->TakeDamage(SkillDamage, DmgEvent, SkillOwner->GetController(), this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("[Thunder] Server Attack Monster : %d"), SkillDamage));
		}
		else
		{
			SkillOwner->ServerAttack(Monster, SkillDamage, DmgEvent, SkillOwner->GetController(), this);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, FString::Printf(TEXT("[Thunder] Client Attack Monster : %d"), SkillDamage));
		}
	}
}

void AThunder::SkillBegin()
{
	// Skill Color Set
	switch (Job)
	{
	case EWizardJob::Blue:
		Color = FVector(0.0f, 3.0f, 8.0f);
		break;
	}
	mParticle->SetVectorParameter(TEXT("color"), Color);

	// Activate
	mParticle->Activate();
	mOutSideCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AThunder::OnSkillOver(FName EventName, float EmitterTime, int32 ParticleTime, const FVector& Location, const FVector& Velocity, const FVector& Direction)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Purple, FString::Printf(TEXT("[Thunder] OnParticleDeath")));
}

void AThunder::Initialize(AWizard* owner, int32 damage, EWizardJob job)
{
	SkillOwner = owner;
	SkillDamage = damage;
	Job = job;

	SkillBegin();
}
