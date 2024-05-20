// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "AIMonsterPawn.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAIMonsterPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	AAIMonsterPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
