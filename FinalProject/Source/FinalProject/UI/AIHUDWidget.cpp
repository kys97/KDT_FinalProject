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
}

void UAIHUDWidget::BindAnimation()
{
	// Animation 정보는 Property 안에 들어가 있다.
	// Property는 LinkedList 방식으로 저장되어 있다.
	// 그래서 시작점 노드의 주소를 얻어온다.
	FProperty* Prop = GetClass()->PropertyLink;

	while (Prop)
	{
		if (Prop->GetClass() == FObjectProperty::StaticClass())
		{
			FObjectProperty* ObjProp = Cast<FObjectProperty>(Prop);
			
			// 이 오브젝트 프로퍼티의 클래스 타입이 UWidgetAnimation인지를 판단 
			if (ObjProp->PropertyClass == UWidgetAnimation::StaticClass())
			{
				UObject* Obj = ObjProp->GetObjectPropertyValue_InContainer(this);

				UWidgetAnimation* Anim = Cast<UWidgetAnimation>(Obj);

				if (Anim)
				{
					// 이름에 따라 원하는 애니메이션인지를 판단하고
					// 해당 애니메이션에 대입해준다. 
					if (Anim->MovieScene->GetFName() == TEXT("DamageAnim"))
						mDamageAnim = Anim;
				}
			}
		}

		Prop = Prop->PropertyLinkNext;
	}
}
