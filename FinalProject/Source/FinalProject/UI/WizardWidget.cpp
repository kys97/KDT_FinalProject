// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardWidget.h"

void UWizardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UWizardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UWizardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HP_PB")));
	mMPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("MP_PB")));
}

void UWizardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UWizardWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// HP Bar Set
	if (mChangeHP)
	{
		tempHp = mChangeHPAmount * InDeltaTime * mGainOrLooseHP * 2;
		mHPBar->SetPercent(mHPBar->GetPercent() + tempHp);
	
		if ((mGainOrLooseHP > 0 && mHPBar->GetPercent() > mTargetHP) || (mGainOrLooseHP < 0 && mHPBar->GetPercent() < mTargetHP))
		{
			mHPBar->SetPercent(mTargetHP);
			mChangeHP = false;
		}
	}

	// MP Bar Set
	if (mChangeMP)
	{
		tempMp = mChangeMPAmount * InDeltaTime * mGainOrLooseMP * 2;
		mMPBar->SetPercent(mMPBar->GetPercent() + tempMp);

		if ((mGainOrLooseMP > 0 && mMPBar->GetPercent() > mTargetMP) || (mGainOrLooseMP < 0 && mMPBar->GetPercent() < mTargetMP))
		{
			mMPBar->SetPercent(mTargetMP);
			mChangeMP = false;
		}
	}
}

void UWizardWidget::SetHPBar(const float hp_per)
{
	mChangeHP = false;
	mTargetHP = hp_per;

	if (mHPBar->GetPercent() > hp_per) // loose hp : --
	{
		mGainOrLooseHP = -1;
		mChangeHPAmount = mHPBar->GetPercent() - hp_per;
	}
	else //  gain hp : ++
	{
		mGainOrLooseHP = 1;
		mChangeHPAmount = hp_per - mHPBar->GetPercent();
	}

	mChangeHP = true;
}

void UWizardWidget::SetMPBar(const float mp_per)
{
	mChangeMP = false;
	mTargetMP = mp_per;

	if (mMPBar->GetPercent() > mp_per) // loose hp : --
	{
		mGainOrLooseMP = -1;
		mChangeMPAmount = mMPBar->GetPercent() - mp_per;
	}
	else //  gain hp : ++
	{
		mGainOrLooseMP = 1;
		mChangeMPAmount = mp_per - mMPBar->GetPercent();
	}

	mChangeMP = true;
}