// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "WizardWidget.h"


void UGameWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UGameWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// mWizardWidget = CreateWidget<UWizardWidget>(GetWidgetFromName(TEXT("WizardWidget")));
}

void UGameWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UGameWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UGameWidget::SetHPBar(const float hp_per)
{
	WizardWidget->SetHPBar(hp_per);
}

void UGameWidget::SetMPBar(const float mp_per)
{
	WizardWidget->SetMPBar(mp_per);
}
