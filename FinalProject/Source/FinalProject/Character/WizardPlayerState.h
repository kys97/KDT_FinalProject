// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "WizardPlayerState.generated.h"





// 직업별 초기 데이터 정보들
USTRUCT(BlueprintType)
struct FWizardData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EWizardJob mJob = EWizardJob::Blue;

	UPROPERTY(EditAnywhere)
	float mNormalAttackPoint = 100.f;
	UPROPERTY(EditAnywhere)
	float mNormalAttackDistance = 350.f;

	UPROPERTY(EditAnywhere)
	float mFirstSkillAttackDamage = 500.f;
	UPROPERTY(EditAnywhere)
	float mFirstSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	float mFisrstSkillCoolTime = 10.f;
	
	UPROPERTY(EditAnywhere)
	float mSecondSkillAttackDamage = 500.f;
	UPROPERTY(EditAnywhere)
	float mSecondSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	float mSecondSkillCoolTime = 10.f;

	UPROPERTY(EditAnywhere)
	float mThirdSkillAttackDamage = 500.f;
	UPROPERTY(EditAnywhere)
	float mThirdSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	float mThirdSkillCoolTime = 10.f;

	UPROPERTY(EditAnywhere)
	float mFourthSkillAttackDamage = 500.f;
	UPROPERTY(EditAnywhere)
	float mFourthSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	float mFourthSkillCoolTime = 10.f;


	UPROPERTY(EditAnywhere)
	float mArmorPoint = 100.f;

	UPROPERTY(EditAnywhere)
	int32 mHPMax = 1000;
	UPROPERTY(EditAnywhere)
	int32 mMPMax = 500;
};


// 플레이어가 실제로 들고 있어야 하는 정보들
UCLASS()
class FINALPROJECT_API AWizardPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AWizardPlayerState();

private:
	UDataTable* mWizardDataTable;

public:
	FString mName;

	EWizardJob mJob;


	float mNormalAttackPoint;
	float mNormalAttackDistance;

	float mFirstSkillAttackDamage;
	float mFirstSkillAttackDistance;
	float mFirstSkillCoolTime;

	float mSecondSkillAttackDamage;
	float mSecondSkillAttackDistance;
	float mSecondSkillCoolTime;

	float mThirdSkillAttackDamage;
	float mThirdSkillAttackDistance;
	float mThirdSkillCoolTime;

	float mFourthSkillAttackDamage;
	float mFourthSkillAttackDistance;
	float mFourthSkillCoolTime;

	float mArmorPoint;

	float mHP;
	int32 mHPMax;

	float mMP;
	int32 mMPMax;
	
	int32 mLevel;
	float mExp;

protected:
	virtual void BeginPlay() override;

};
