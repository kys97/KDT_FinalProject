// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EffectBase.h"
#include "Effect_FireEmit.generated.h"


UCLASS()
class FINALPROJECT_API AEffect_FireEmit : public AEffectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEffect_FireEmit();

protected:
	AActor* OverlapActor = nullptr;

	bool mIsOverlap = false;
	float mAttackTime = 0.f;
	float mAttackDuration = 1.f;

	int32 mSkillPower = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	float GetCapsuleHalfHeight()
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}

	void SetSkillPower(int32 Power)
	{
		mSkillPower = Power;
	}
};
