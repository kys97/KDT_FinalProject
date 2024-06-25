// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIMonsterPawn.h"
#include "AIDragonTheSoulEater.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAIDragonTheSoulEater : public AAIMonsterPawn
{
	GENERATED_BODY()

public:
	AAIDragonTheSoulEater();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();
	virtual EMonsterType GetMonsterType()
	{
		return EMonsterType::Nomal;
	}
};
