// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardSkill.h"

void UWizardSkill::NativeConstruct()
{
	Super::NativeConstruct();

	mFirstSkillPB = Cast<UProgressBar>(GetWidgetFromName(TEXT("FirstSkill_PB")));
	mSecondSkillPB = Cast<UProgressBar>(GetWidgetFromName(TEXT("SecondSkill_PB")));
	mThirdSkillPB = Cast<UProgressBar>(GetWidgetFromName(TEXT("ThirdSkill_PB")));

	mFirstCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("FirstSkillCount_TB")));
	mSecondCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("SecondSkillCount_TB")));
	mThirdCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("ThirdSkillCount_TB")));

	mFirstSkillPB->SetPercent(0);
	mSecondSkillPB->SetPercent(0);
	mThirdSkillPB->SetPercent(0);

	mFirstCountTB->SetText(FText::FromString(""));
	mSecondCountTB->SetText(FText::FromString(""));
	mThirdCountTB->SetText(FText::FromString(""));
}

void UWizardSkill::SetFirstSkillCoolTime(const int32 remind_time, const float cooltime)
{
	mFirstSkillPB->SetPercent(remind_time / cooltime);
	mFirstCountTB->SetText(FText::AsNumber(remind_time));
}

void UWizardSkill::SetSecondSkillCoolTime(const int32 remind_time, const float cooltime)
{
	mSecondSkillPB->SetPercent(remind_time / cooltime);
	mSecondCountTB->SetText(FText::AsNumber(remind_time));
}

void UWizardSkill::SetThirdSkillCoolTime(const int32 remind_time, const float cooltime)
{
	mThirdSkillPB->SetPercent(remind_time / cooltime);
	mThirdCountTB->SetText(FText::AsNumber(remind_time));
}

void UWizardSkill::EndFirstSkillCoolTime()
{
	mFirstCountTB->SetText(FText::FromString(""));
}

void UWizardSkill::EndSecondSkillCoolTime()
{
	mSecondCountTB->SetText(FText::FromString(""));
}

void UWizardSkill::EndThirdSkillCoolTime()
{
	mThirdCountTB->SetText(FText::FromString(""));
}
