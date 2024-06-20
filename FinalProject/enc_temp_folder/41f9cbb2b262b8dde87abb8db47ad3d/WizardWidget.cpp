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
}

void UWizardWidget::SetHPBar(const float hp_per)
{
	mHPBar->SetPercent(hp_per);
}

void UWizardWidget::SetMPBar(const float mp_per)
{
	mMPBar->SetPercent(mp_per);
}
