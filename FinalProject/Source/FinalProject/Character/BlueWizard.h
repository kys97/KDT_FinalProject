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


	UFUNCTION(Server, Reliable)
	void ServerFirstSkillSpawn(FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage);
	UFUNCTION(NetMulticast, Reliable)
	void FirstSkillSpawn(FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage);


	UFUNCTION(Server, Reliable)
	void ServerSecondSkillSpawn(FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage, EWizardJob Job);
	UFUNCTION(NetMulticast, Reliable)
	void SecondSkillSpawn(FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage, EWizardJob Job);


	UFUNCTION(Server, Reliable)
	void ServerThirdSkillSpawn(FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage);
	UFUNCTION(NetMulticast, Reliable)
	void ThirdSkillSpawn(FVector SpawnLocation, FRotator SpawnRotation, int32 SkillDamage);

};
