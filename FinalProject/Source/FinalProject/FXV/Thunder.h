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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void SkillBegin();
	void SkillOver();

};
