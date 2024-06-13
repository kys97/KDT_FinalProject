// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "SkillParticleActor.h"
#include "Thunder.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AThunder : public ASkillParticleActor
{
	GENERATED_BODY()

public:
	AThunder();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EWizardJob Job;

	bool Init = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Color;

private:
	float timer = 0.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnSkillOver(FName EventName, float EmitterTime, int32 ParticleTime, const FVector& Location, const FVector& Velocity, const FVector& Direction);

private:
	void SkillBegin();
	
public:
	void Initialize(AWizard* owner, int32 damage, EWizardJob job);
};
