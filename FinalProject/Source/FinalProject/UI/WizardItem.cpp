// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardItem.h"

void UWizardItem::NativeConstruct()
{
	Super::NativeConstruct();

	mHPItemImg = Cast<UImage>(GetWidgetFromName(TEXT("HPItem_Imge")));
	mMPItemImg = Cast<UImage>(GetWidgetFromName(TEXT("MPItem_Imge")));
	mAttackItemPB = Cast<UProgressBar>(GetWidgetFromName(TEXT("AttackItem_PB")));
	mArmorItemPB = Cast<UProgressBar>(GetWidgetFromName(TEXT("ArmorItem_PB")));

	mHPCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPCnt_TB")));
	mMPCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPCnt_TB")));
	mAttackCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("AttackCnt_TB")));
	mArmorCountTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("ArmorCnt_TB")));
}

void UWizardItem::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (IsUseAttackItem)
	{
		attack_cooltime += InDeltaTime;
		if (attack_cooltime / 60.f > 1)
			mAttackItemPB->SetPercent(1);
		else
			mAttackItemPB->SetPercent(attack_cooltime / 60.f);
	}

	if (IsUseArmorItem)
	{
		armor_cooltime += InDeltaTime;
		if (armor_cooltime / 60.f > 1)
			mArmorItemPB->SetPercent(1);
		else
			mArmorItemPB->SetPercent(armor_cooltime / 60.f);
	}
}


void UWizardItem::SetHPItemCount(int32 hp_cnt)
{
	if (hp_cnt > 0)
	{
		mHPCountTB->SetText(FText::FromString(FString::Printf(TEXT("%d"), hp_cnt)));
		mHPCountTB->SetColorAndOpacity(FSlateColor(mItemTextColor));
		mHPItemImg->SetColorAndOpacity(mItemImageColor);
	}
	else if(hp_cnt == 0)
	{
		mHPCountTB->SetText(FText::FromString("0"));
		mHPCountTB->SetColorAndOpacity(FSlateColor(mNoItemTextColor));
		mHPItemImg->SetColorAndOpacity(mNoItemImageColor);
	}
}
void UWizardItem::SetMPItemCount(int32 mp_cnt)
{
	if (mp_cnt > 0)
	{
		mMPCountTB->SetText(FText::FromString(FString::Printf(TEXT("%d"), mp_cnt)));
		mMPCountTB->SetColorAndOpacity(FSlateColor(mItemTextColor));
		mMPItemImg->SetColorAndOpacity(mItemImageColor);
	}
	else if (mp_cnt == 0)
	{
		mMPCountTB->SetText(FText::FromString("0"));
		mMPCountTB->SetColorAndOpacity(FSlateColor(mNoItemTextColor));
		mMPItemImg->SetColorAndOpacity(mNoItemImageColor);
	}
}
void UWizardItem::SetAttackItemCount(int32 attackitem_cnt)
{
	if (attackitem_cnt > 0)
	{
		mAttackCountTB->SetText(FText::FromString(FString::Printf(TEXT("%d"), attackitem_cnt)));
		mAttackCountTB->SetColorAndOpacity(FSlateColor(mItemTextColor));
		mAttackItemPB->SetPercent(0);
	}
	else if (attackitem_cnt == 0)
	{
		mAttackCountTB->SetText(FText::FromString("0"));
		mAttackCountTB->SetColorAndOpacity(FSlateColor(mNoItemTextColor));
		mAttackItemPB->SetPercent(1);
	}
}
void UWizardItem::SetArmorItemCount(int32 armoritem_cnt)
{
	if (armoritem_cnt > 0)
	{
		mArmorCountTB->SetText(FText::FromString(FString::Printf(TEXT("%d"), armoritem_cnt)));
		mArmorCountTB->SetColorAndOpacity(FSlateColor(mItemTextColor));
		mArmorItemPB->SetPercent(0);
	}
	else if (armoritem_cnt == 0)
	{
		mArmorCountTB->SetText(FText::FromString("0"));
		mArmorCountTB->SetColorAndOpacity(FSlateColor(mNoItemTextColor));
		mArmorItemPB->SetPercent(1);
	}
}


// 0 -> 1
void UWizardItem::UseAttackItem()
{
	IsUseAttackItem = true;
}
void UWizardItem::EndAttackItem()
{
	IsUseAttackItem = false;
	attack_cooltime = 0.f;

	if (mAttackCountTB->GetText().ToString() == "0")
		mAttackItemPB->SetPercent(1);
	else
		mAttackItemPB->SetPercent(0);
}

void UWizardItem::UseArmorItem()
{
	IsUseArmorItem = true;
}

void UWizardItem::EndArmorItem()
{
}
