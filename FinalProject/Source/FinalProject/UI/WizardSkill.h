// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"


#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


#include "Blueprint/UserWidget.h"
#include "WizardSkill.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UWizardSkill : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UProgressBar* mFirstSkillPB;
	UProgressBar* mSecondSkillPB;
	UProgressBar* mThirdSkillPB;

	UTextBlock* mFirstCountTB;
	UTextBlock* mSecondCountTB;
	UTextBlock* mThirdCountTB;

protected:
	virtual void NativeConstruct();

public:
	void SetFirstSkillCoolTime(const int32 remind_time, const float cooltime);
	void SetSecondSkillCoolTime(const int32 remind_time, const float cooltime);
	void SetThirdSkillCoolTime(const int32 remind_time, const float cooltime);

	void EndFirstSkillCoolTime();
	void EndSecondSkillCoolTime();
	void EndThirdSkillCoolTime();
};
