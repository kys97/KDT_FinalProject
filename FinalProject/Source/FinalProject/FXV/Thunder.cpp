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

	// Enable Set
	GetRootComponent()->bAutoActivate = false;
}

void AThunder::BeginPlay()
{
	Super::BeginPlay();
	
	// Delay
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AThunder::BeginDelayOver, 0.5f, false);
}

void AThunder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThunder::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(SkillOwner)
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("[Thunder] SkillOwner True")));
	else
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("[Thunder] SkillOwner False")));


	AAIMonsterPawn* Monster = Cast<AAIMonsterPawn>(OtherActor);
	if (Monster && SkillOwner)
	{
		// Monster->TakeDamage()
		FDamageEvent DmgEvent;
		if (SkillOwner->HasAuthority())
		{
			Monster->TakeDamage(SkillDamage, DmgEvent, SkillOwner->GetController(), this);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("[Thunder] Server Attack Monster : %d"), SkillDamage));
		}
		else 
		{
			SkillOwner->ServerAttack(Monster, SkillDamage, DmgEvent, SkillOwner->GetController(), this);
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Cyan, FString::Printf(TEXT("[Thunder] Client Attack Monster : %d"), SkillDamage));
		}
	}
}

void AThunder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}

void AThunder::BeginDelayOver()
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
}