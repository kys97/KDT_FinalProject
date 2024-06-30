// Fill out your copyright notice in the Description page of Project Settings.


#include "AIHUDWidget.h"
#include "Animation/widgetAnimation.h"
#include "MovieScene.h"

void UAIHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mNameText = Cast<UTextBlock>(GetWidgetFromName(TEXT("AINameText")));
	mMonsterHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("AIHPBar")));
	mBossHPBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("BossHPBar")));

	mDamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("DamageText")));
	BindAnimation();

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

		if (mMonsterType == EMonsterType::Nomal) {
			mMonsterHPBar->SetPercent(NewPercent);
		}
		else if (mMonsterType == EMonsterType::Boss){
			mBossHPBar->SetPercent(NewPercent);
		}

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

void UAIHUDWidget::SetWidgetDamageText(int32 Damage)
{
	FString SDamage = FString::FromInt(Damage);
	mDamageText->SetText(FText::FromString(SDamage));

	PlayAnimation(mDamageAnim, 0.f, 1, EUMGSequencePlayMode::Forward);
}

void UAIHUDWidget::BindAnimation()
{
	// ButtonScale Property를 얻어온다.
	FProperty* Prop = GetClass()->FindPropertyByName(TEXT("DamageAnim"));

	// FObjectProperty로 형변환한다.
	FObjectProperty* ObjProp = CastField<FObjectProperty>(Prop);

	if (ObjProp)
	{
		// WidgetAnimation 타입인지 판단한다.
		if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
		{
			// ObjectProperty로부터 실제 WidgetAnimation 객체를
			// 얻어온다.
			UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);

			// UObject로 얻어온 객체를 WidgetAnimation 타입으로
			// 형변환한다.
			UWidgetAnimation* Anim = Cast<UWidgetAnimation>(Obj);

			mDamageAnim = Anim;
		}
	}
}
