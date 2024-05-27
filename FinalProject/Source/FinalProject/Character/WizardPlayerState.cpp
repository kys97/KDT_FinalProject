// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerState.h"

AWizardPlayerState::AWizardPlayerState()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> WizardDataAsset(TEXT("/Script/Engine.DataTable'/Game/Blueprint/Character/DT_Wizard.DT_Wizard'"));
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
		mArmorPoint = Data->mArmorPoint;
		mHPMax = Data->mHPMax;
		mMPMax = Data->mMPMax;
		
		// TODO : mName Set
		mHP = mHPMax;
		mMP = mMPMax;
		mLevel = 1;
		mExp = 0;
	}
}