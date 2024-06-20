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

	if (mIsAttack)
	{
		tempHp = mNewHp * InDeltaTime * mSpeed;
		mHPBar->SetPercent(mHPBar->GetPercent() - tempHp);
		mNewHp -= tempHp;
		
		if (mNewHp < 0.0001f)
		{
			mHPBar->SetPercent(mHPBar->GetPercent() - mNewHp);
			mNewHp = 0.f;
			mIsAttack = false;
		}
	}

	if (mUseSkill)
	{
		tempMp = mNewMp * InDeltaTime * mSpeed;
		mMPBar->SetPercent(mMPBar->GetPercent() - tempMp);
		mNewMp -= tempMp;

		if (mNewMp < 0.0001f)
		{
			mMPBar->SetPercent(mMPBar->GetPercent() - mNewMp);
			mNewMp = 0.f;
			mUseSkill = false;
		}
	}
}

void UWizardWidget::SetHPBar(const float hp_per)
{
	if (mHPBar->GetPercent() > hp_per)
	{
		mNewHp = mHPBar->GetPercent() - hp_per;
		mIsAttack = true;
	}
	else
	{
		mHPBar->SetPercent(hp_per);
	}
}

void UWizardWidget::SetMPBar(const float mp_per)
{
	if (mMPBar->GetPercent() > mp_per)
	{
		mNewMp = mMPBar->GetPercent() - mp_per;
		mUseSkill = true;
	}
	else
	{
		mMPBar->SetPercent(mp_per);
	}
}