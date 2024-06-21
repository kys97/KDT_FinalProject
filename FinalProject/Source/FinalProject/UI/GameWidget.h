// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"



#include "Blueprint/UserWidget.h"
#include "GameWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	class UWizardWidget* WizardWidget;

	UPROPERTY(meta = (BindWidget))
	class UWizardSkill* WizardSkillWidget;

protected:
	// 위젯 생성시 한번
	virtual void NativeOnInitialized();

	// AddToViewport
	virtual void NativePreConstruct();
	virtual void NativeConstruct(); // 생성

	// Viewport에서 Remove될때
	virtual void NativeDestruct();

	// Tick
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	void SetHPBar(const float hp_per);
	void SetMPBar(const float mp_per);

	void SetFirstSkillCoolTime(const int32 remind_time, const float cooltime);
	void SetSecondSkillCoolTime(const int32 remind_time, const float cooltime);
	void SetThirdSkillCoolTime(const int32 remind_time, const float cooltime);

	void EndFirstSkillCoolTime();
	void EndSecondSkillCoolTime();
	void EndThirdSkillCoolTime();
};
