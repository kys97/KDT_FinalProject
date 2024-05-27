// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIPawn.h"
#include "AIMonsterPawn.generated.h"


UCLASS()
class FINALPROJECT_API AAIMonsterPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	AAIMonsterPawn();

protected:
	class UMonsterAnimInstance* mAnimInst;

	bool mOverlap;

public:
	virtual void ChangeAIAnimType(uint8 AnimType);

	virtual bool AIIsOverlap()
	{
		return mOverlap;
	}

	virtual void ChangeOverlapVlaue(bool Value)
	{
		mOverlap = Value;
	}

	virtual void NormalAttack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};

