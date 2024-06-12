// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wizard.h"
#include "BlueWizard.generated.h"


UCLASS()
class FINALPROJECT_API ABlueWizard : public AWizard
{
	GENERATED_BODY()

public:
	ABlueWizard();

protected:
	UStaticMesh* mWeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AStorm> mFirstSkillParticle;
	TSubclassOf<class AThunder> mSecondSkillParticle;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void NormalAttack() override;
	virtual void FirstSkill() override;
	virtual void SecondSkill() override;
	virtual void ThirdSkill() override;
	virtual void FourthSkill() override;

private:
	void PlayAttackAnimation(AWizard* TargetWizard, EWizardAttackAnimTypes AnimType);
};
