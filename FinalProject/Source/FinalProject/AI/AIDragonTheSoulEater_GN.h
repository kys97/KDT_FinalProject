// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIDragonTheSoulEater.h"
#include "AIDragonTheSoulEater_GN.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAIDragonTheSoulEater_GN : public AAIDragonTheSoulEater
{
	GENERATED_BODY()
	
public:
	AAIDragonTheSoulEater_GN ();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NormalAttack();
};
