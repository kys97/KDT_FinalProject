// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Blueprint/UserWidget.h"
#include "AIHUDWidget.generated.h"

DECLARE_MULTICAST_DELEGATE(FConstructDelegate)

UCLASS()
class FINALPROJECT_API UAIHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UTextBlock* mNameText;
	UProgressBar* mHPBar;

	FConstructDelegate mConstructDelegate;

protected:
	// AddToViewport 시 호출
	virtual void NativeConstruct();

public:
	void SetAIName(const FString& Name);
	void SetAIHP(float HPPercent);
	
	// 등록할 함수의 타입을 알 수 없으니 template
	template <typename T>
	void AddConstructDelegate(T* Obj, void(T::* Func)())
	{
		mConstructDelegate.AddUObject(Obj, Func);
	}
};
