// Fill out your copyright notice in the Description page of Project Settings.


#include "Thunder.h"




AThunder::AThunder()
{
	PrimaryActorTick.bCanEverTick = true;

	// Thunder Particle Set
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ThunderParticle{ TEXT("/Script/Engine.ParticleSystem'/Game/Blueprint/FXV/P_ky_lightning.P_ky_lightning'") };
	if (ThunderParticle.Succeeded())
	{
		mParticle->SetTemplate(ThunderParticle.Object);
	}

	// OutSide Collision Set
	mOutSideCollision->SetCapsuleSize(180.f, 350.f);
	mOutSideCollision->SetRelativeLocation(FVector(0.f, 0.f, 165.f));

	// Skill Color Set
	switch (Job)
	{
		case EWizardJob::Blue: Color = FVector(0.0f, 3.0f, 8.0f);
	}
	mParticle->SetVectorParameter(TEXT("color"), Color);
}

void AThunder::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Yellow, FString::Printf(TEXT("Thunder Spawn")));
}

void AThunder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThunder::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
}

void AThunder::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
}
