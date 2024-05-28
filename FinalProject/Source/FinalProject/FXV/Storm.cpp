// Fill out your copyright notice in the Description page of Project Settings.


#include "Storm.h"

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

	// InSide Collision Set
	mInsideCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("InsideCollision"));
	mInsideCollision->SetupAttachment(GetRootComponent());
	mInsideCollision->SetCapsuleSize(90.f, 370.f);
	mInsideCollision->SetRelativeLocation(FVector(0.f, 0.f, 270.f));
	mInsideCollision->SetCollisionProfileName(TEXT("Skill"));

	// Enable Set
	GetRootComponent()->bAutoActivate = false;

	// Var Set
	mScale = 0.2f;
	mFadeSpeed = 0.5f;
	mMoveSpeed = 1.f;
}

// Called when the game starts or when spawned
void AStorm::BeginPlay()
{
	Super::BeginPlay();
	
	// Scale Init
	mParticle->SetRelativeScale3D(FVector(1, 1, 1) * mScale);


}

// Called every frame
void AStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

