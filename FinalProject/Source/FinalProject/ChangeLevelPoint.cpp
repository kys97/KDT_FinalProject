// Fill out your copyright notice in the Description page of Project Settings.


#include "ChangeLevelPoint.h"
#include "Character/Wizard.h"

// Sets default values
AChangeLevelPoint::AChangeLevelPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	mTrigger->SetupAttachment(mRoot);

	mTrigger->SetCollisionProfileName(TEXT("PlayerTrigger"));

	mRoot->bVisualizeComponent = true;

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("StonParticle"));
	mParticle->SetupAttachment(mRoot);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle{ TEXT("/Script/Engine.ParticleSystem'/Game/AI/Asset/Particle/P_Summon_Portal.P_Summon_Portal'") };
	if (Particle.Succeeded())
	{
		mParticle->SetTemplate(Particle.Object);
	}

	mParticle->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
}

// Called when the game starts or when spawned
void AChangeLevelPoint::BeginPlay()
{
	Super::BeginPlay();
	
	mTrigger->OnComponentBeginOverlap.AddDynamic(this, &AChangeLevelPoint::BeginOverlap);
}

// Called every frame
void AChangeLevelPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChangeLevelPoint::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	AWizard* WizardPlayer = Cast<AWizard>(OtherActor);
	if (WizardPlayer)
	{
		WizardPlayer->SaveWizardInfo();
	}

	UGameplayStatics::OpenLevel(GetWorld(), mLevelName);
}
