// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIMonsterPawn.h"
#include "Bose_RamPage.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ABose_RamPage : public AAIMonsterPawn
{
	GENERATED_BODY()

public:
	ABose_RamPage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();
};
