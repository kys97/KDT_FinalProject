// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

#include "WizardItem.h"
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

void UGameWidget::SetAttackItemCount(const int32 last_cnt)
{
	WizardItemWidget->SetAttackItemCount(last_cnt);
}

void UGameWidget::SetArmorItemCount(const int32 last_cnt)
{
	WizardItemWidget->SetArmorItemCount(last_cnt);
}

#pragma region Item UI

void UGameWidget::UseHPpotionItem(const int32 last_cnt)
{
	WizardItemWidget->SetHPItemCount(last_cnt);
}

void UGameWidget::UseMPpotionItem(const int32 last_cnt)
{
	WizardItemWidget->SetMPItemCount(last_cnt);
}

void UGameWidget::UseAttackPointItem(const int32 last_cnt)
{
	WizardItemWidget->UseAttackItem();
	SetAttackItemCount(last_cnt);
}

void UGameWidget::UseArmorPointItem(const int32 last_cnt)
{
	WizardItemWidget->UseArmorItem();
	SetArmorItemCount(last_cnt);
}

void UGameWidget::EndAttackPointItem()
{
	WizardItemWidget->EndAttackItem();
}

void UGameWidget::EndArmorPointItem()
{
	WizardItemWidget->EndArmorItem();
}

#pragma endregion

#pragma region HP/MP UI

void UGameWidget::SetHPBar(const float hp_per)
{
	WizardWidget->SetHPBar(hp_per);
}

void UGameWidget::SetMPBar(const float mp_per)
{
	WizardWidget->SetMPBar(mp_per);
}

#pragma endregion

#pragma region Skill Cool Time UI

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

#pragma endregion

void UGameWidget::PlayerDeath()
{
	WizardDeathWidget->SetDeathWidgetEnable();
}
