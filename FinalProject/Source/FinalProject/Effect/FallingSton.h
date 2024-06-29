// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EffectBase.h"
#include "FallingSton.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AFallingSton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFallingSton();

protected:
	UPROPERTY(EditAnywhere)
	UGeometryCollectionComponent* mStonDestroyComp;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* mStonFireParticle;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* TileMoveComp;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* mFloorParticle;

	UPROPERTY(EditAnywhere)
	UParticleSystem* mFallEndFloorEffect;

	AActor* OverlapActor = nullptr;

	int32 mSkillPower = 0;

	bool mIsOverlap = false;
	float mAttackTime = 0.f;
	float mAttackDuration = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

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

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, const FHitResult& Hit);

public:
	float GetCapsuleHalfHeight()
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}
	float GetCapsuleRadius()
	{
		return mCapsule->GetScaledCapsuleRadius();
	}

	void SetSkillPower(int32 Power)
	{
		mSkillPower = Power;
	}
};
