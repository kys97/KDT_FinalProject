// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Blueprint/UserWidget.h"
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
	float mSpeed = 20.f;

	bool mIsAttack = false;
	float mNewHp;
	float tempHp;

	bool mChangeMP = false;
	int mGainOrLoose = 0;
	float mNewMp;
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
