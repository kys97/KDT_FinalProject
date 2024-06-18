// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillParticleActor.h"
#include "../Character/WizardPlayerState.h"

// Sets default values
ASkillParticleActor::ASkillParticleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Particle Set
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fx"));
	SetRootComponent(mParticle);

	// Collison Set
	mOutSideCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OutsideCollision"));
	mOutSideCollision->SetupAttachment(GetRootComponent());
	mOutSideCollision->SetCollisionProfileName(TEXT("Skill"));
	mOutSideCollision->CanCharacterStepUpOn = ECB_No;

	// Set Replicate
	SetReplicates(true);
	SetReplicateMovement(true);
}

// Called when the game starts or when spawned
void ASkillParticleActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASkillParticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASkillParticleActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
