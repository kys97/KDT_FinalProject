// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "WizardWidget.h"
#include "WizardSkill.h"
#include "WizardDeathWidget.h"


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

void UGameWidget::SetFirstSkillCoolTime(const int32 remind_time, const float cooltime)
{
	WizardSkillWidget->SetFirstSkillCoolTime(remind_time, cooltime);
}

void UGameWidget::SetSecondSkillCoolTime(const int32 remind_time, const float cooltime)
{
	WizardSkillWidget->SetSecondSkillCoolTime(remind_time, cooltime);
}

void UGameWidget::SetThirdSkillCoolTime(const int32 remind_time, const float cooltime)
{
	WizardSkillWidget->SetThirdSkillCoolTime(remind_time, cooltime);
}

void UGameWidget::EndFirstSkillCoolTime()
{
	WizardSkillWidget->EndFirstSkillCoolTime();
}

void UGameWidget::EndSecondSkillCoolTime()
{
	WizardSkillWidget->EndSecondSkillCoolTime();
}

void UGameWidget::EndThirdSkillCoolTime()
{
	WizardSkillWidget->EndThirdSkillCoolTime();
}

void UGameWidget::PlayerDeath()
{
	WizardDeathWidget->SetDeathWidgetEnable();
}
