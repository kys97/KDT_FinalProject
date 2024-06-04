// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPointActor.h"

// Sets default values
APatrolPointActor::APatrolPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	mTrigger->SetupAttachment(mRoot);

	mTrigger->SetBoxExtent(FVector(30.0, 30.0, 100.0));
	mTrigger->SetRelativeLocation(FVector(0.0, 0.0, 100.0));

	mTrigger->SetCollisionProfileName(TEXT("MonsterTrigger"));

#if WITH_EDITORONLY_DATA

	mRoot->bVisualizeComponent = true;

#endif
}

// Called when the game starts or when spawned
void APatrolPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

