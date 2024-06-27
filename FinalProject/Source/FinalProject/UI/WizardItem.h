// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "WizardItem.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UWizardItem : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UImage* mHPItemImg;
	UImage* mMPItemImg;
	UProgressBar* mAttackItemPB;
	UProgressBar* mArmorItemPB;

	UTextBlock* mHPCountTB;
	UTextBlock* mMPCountTB;
	UTextBlock* mAttackCountTB;
	UTextBlock* mArmorCountTB;

	
	FLinearColor mNoItemImageColor = FLinearColor(0.291667f, 0.291667f, 0.5f, 0.5f);
	FLinearColor mItemImageColor = FLinearColor(0.291667f, 0.291667f, 0.5f, 0.f);
	FLinearColor mNoItemTextColor = FLinearColor(1.f, 0.114435f, 0.147027f, 1.f);
	FLinearColor mItemTextColor = FLinearColor(0.130136f, 0.552011f, 0.775822f, 1.f);

private:
	bool IsUseAttackItem = false;
	bool IsUseArmorItem = false;

	float attack_cooltime = 0.f;
	float armor_cooltime = 0.f;

protected:
	virtual void NativeConstruct();
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

public:
	// Set Count
	void SetHPItemCount(int32 hp_cnt);
	void SetMPItemCount(int32 mp_cnt);
	void SetAttackItemCount(int32 attackitem_cnt);
	void SetArmorItemCount(int32 armoritem_cnt);

	// Set Time
	void UseAttackItem();
	void EndAttackItem();
	void UseArmorItem();
	void EndArmorItem();
};
