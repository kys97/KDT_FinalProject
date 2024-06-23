// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIMonsterPawn.h"
#include "Boss_RamPage.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API ABoss_RamPage : public AAIMonsterPawn
{
	GENERATED_BODY()

public:
	ABoss_RamPage();

protected:
	UPROPERTY(VisibleAnywhere)
	class AEffect_FireEmit* mEmitEffect;

	AActor* SkillActor = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SkillSetting(int32 Num);
	virtual void SkillDestroy()
	{
		SkillActor->Destroy();
	}
};
