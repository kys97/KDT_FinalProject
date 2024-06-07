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
	int32 mNormalAttackPoint = 20.f;
	UPROPERTY(EditAnywhere)
	float mNormalAttackDistance = 350.f;

	UPROPERTY(EditAnywhere)
	int32 mFirstSkillAttackDamage = 100.f;
	UPROPERTY(EditAnywhere)
	float mFirstSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	int32 mSecondSkillAttackDamage = 100.f;
	UPROPERTY(EditAnywhere)
	float mSecondSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	int32 mThirdSkillAttackDamage = 100.f;
	UPROPERTY(EditAnywhere)
	float mThirdSkillAttackDistance = 500.f;
	UPROPERTY(EditAnywhere)
	int32 mFourthSkillAttackDamage = 100.f;
	UPROPERTY(EditAnywhere)
	float mFourthSkillAttackDistance = 500.f;

	UPROPERTY(EditAnywhere)
	int32 mArmorPoint = 10.f;

	UPROPERTY(EditAnywhere)
	int32 mHPMax = 100.f;
	UPROPERTY(EditAnywhere)
	int32 mMPMax = 100.f;
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


	int32 mNormalAttackPoint;
	float mNormalAttackDistance;

	int32 mFirstSkillAttackDamage;
	float mFirstSkillAttackDistance;
	int32 mSecondSkillAttackDamage;
	float mSecondSkillAttackDistance;
	int32 mThirdSkillAttackDamage;
	float mThirdSkillAttackDistance;
	int32 mFourthSkillAttackDamage;
	float mFourthSkillAttackDistance;


	int32 mArmorPoint;

	
	int32 mHP;

	int32 mHPMax;

	
	int32 mMP;

	int32 mMPMax;

	
	int32 mLevel;

	int32 mExp;

protected:
	virtual void BeginPlay() override;

};
