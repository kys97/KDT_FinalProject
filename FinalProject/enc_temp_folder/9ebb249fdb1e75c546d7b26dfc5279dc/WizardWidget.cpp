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
}

void UWizardWidget::SetHPBar(const float hp_per)
{
	if (mHPBar->GetPercent() > hp_per)
	{
		mNewHp = mHPBar->GetPercent() - hp_per;
		mIsAttack = true;


		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("HP Per : %f"), hp_per));
	}
	else
	{
		mIsAttack = false;
		mHPBar->SetPercent(hp_per);
	}
}

void UWizardWidget::SetMPBar(const float mp_per)
{
	mMPBar->SetPercent(mp_per);
}