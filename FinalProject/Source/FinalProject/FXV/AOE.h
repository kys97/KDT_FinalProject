// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "SkillParticleActor.h"
#include "AOE.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API AAOE : public ASkillParticleActor
{
	GENERATED_BODY()
	
public:
	AAOE();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Color;

private:
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCapsuleOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void Initialize(AWizard* owner, int32 damage, EWizardJob job);

private:
	void SkillBegin();
	void SkillOver();
	void SkillDestroy();

};
