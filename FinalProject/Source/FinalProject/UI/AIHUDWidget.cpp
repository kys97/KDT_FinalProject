// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHUDWidget.h"

void UAIHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("AINameText")));
	mHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("AIHPBar")));

	// 함수가 등록되어 있는지 판단해서 등록된 모든 함수 호출
	if (mConstructDelegate.IsBound())
		mConstructDelegate.Broadcast();
}

void UAIHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (mChangeHP)
	{
		mChangeTime += InDeltaTime;
		float Alpha = mChangeTime / mChangeDuration;

		float NewPercent = FMath::Lerp(mOldHPPercent, mHPPercent, Alpha);
		mHPBar->SetPercent(NewPercent);
		
		if (mChangeTime >= mChangeDuration)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Client Log! UAIHUDWidget/mHPPercent : %f"), NewPercent));
			mOldHPPercent = NewPercent;
			mChangeHP = false;
			mChangeTime = 0.f;
		}
	}
}

void UAIHUDWidget::SetAIName(const FString& Name)
{
	mNameText->SetText(FText::FromString(Name));
}

void UAIHUDWidget::SetAIHP(float HPPercent)
{
	mHPPercent = HPPercent;
	mChangeHP = true;
}
