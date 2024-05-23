// Fill out your copyright notice in the Description page of Project Settings.

#include "AIMonsterPawn.h"
#include "DefaultAIController.h"
#include "MonsterAnimInstance.h"

AAIMonsterPawn::AAIMonsterPawn()
{
}

void AAIMonsterPawn::ChangeAIAnimType(uint8 AnimType)
{
	mAnimInst->ChangeAnimType((EMonsterAnimType)AnimType);
}

void AAIMonsterPawn::BeginPlay()
{
	Super::BeginPlay();

	mAnimInst = Cast<UMonsterAnimInstance>(mMesh->GetAnimInstance());
}

void AAIMonsterPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
