// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"

AItemActor::AItemActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Root Conmponent
	mItemParticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ItemNiagara"));
	SetRootComponent(mItemParticle);

	// Set Collision
	mItemCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ItemCollision"));
	mItemCollision->SetupAttachment(GetRootComponent());
	mItemCollision->SetCollisionProfileName(TEXT("Item"));

	// Set Replicate
	SetReplicates(true);
	SetReplicateMovement(true);
}

void AItemActor::BeginPlay()
{
	Super::BeginPlay();
}

void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

