// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerState.h"

AWizardPlayerState::AWizardPlayerState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> WizardDataAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Character/WizardData.WizardData'"));
	if (WizardDataAsset.Succeeded())
	{
		mWizardDataTable = WizardDataAsset.Object;
	}
}

void AWizardPlayerState::BeginPlay()
{
	Super::BeginPlay();

	// Data Init()
	FWizardData* Data = mWizardDataTable->FindRow<FWizardData>(TEXT("Wind"), TEXT(""));
	if (Data)
	{
		mJob = Data->mJob;

		mNormalAttackPoint = Data->mNormalAttackPoint;
		mNormalAttackDistance = Data->mNormalAttackDistance;

		mFirstSkillAttackDamage = Data->mFirstSkillAttackDamage;
		mFirstSkillAttackDistance = Data->mFirstSkillAttackDistance;
		mFirstSkillCoolTime = Data->mFisrstSkillCoolTime;

		mSecondSkillAttackDamage = Data->mSecondSkillAttackDamage;
		mSecondSkillAttackDistance = Data->mSecondSkillAttackDistance;
		mSecondSkillCoolTime = Data->mSecondSkillCoolTime;

		mThirdSkillAttackDamage = Data->mThirdSkillAttackDamage;
		mThirdSkillAttackDistance = Data->mThirdSkillAttackDistance;
		mThirdSkillCoolTime = Data->mThirdSkillCoolTime;

		mFourthSkillAttackDamage = Data->mFourthSkillAttackDamage;
		mFourthSkillAttackDistance = Data->mFourthSkillAttackDistance;
		mFourthSkillCoolTime = Data->mFourthSkillCoolTime;

		mArmorPoint = Data->mArmorPoint;
		mHPMax = Data->mHPMax;
		mMPMax = Data->mMPMax;
		
		// TODO : mName Set
		mHP = mHPMax;
		mMP = mMPMax;
		mLevel = 1;
		mExp = 0.f;
	}
}
