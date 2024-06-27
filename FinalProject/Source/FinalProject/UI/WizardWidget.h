// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/ProgressBar.h"

#include "Blueprint/UserWidget.h"
#include "WizardWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UWizardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UProgressBar* mHPBar;
	UProgressBar* mMPBar;

private:
	bool mChangeHP = false;
	int mGainOrLooseHP = 0;
	float mTargetHP;
	float mChangeHPAmount;
	float tempHp;

	bool mChangeMP = false;
	int mGainOrLooseMP = 0;
	float mTargetMP;
	float mChangeMPAmount;
	float tempMp;

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
};
