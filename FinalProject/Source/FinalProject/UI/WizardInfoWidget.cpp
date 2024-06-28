// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardInfoWidget.h"
#include "../WizardGameInstance.h"

void UWizardInfoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mInfoTB = Cast<UTextBlock>(GetWidgetFromName(TEXT("Info_TB")));

	UWizardGameInstance* Instance = GetGameInstance<UWizardGameInstance>();
	SetWizardInfoText(Instance->GetLevelString().Append(Instance->GetWizardName()));
}

void UWizardInfoWidget::SetWizardInfoText(FString info_string)
{
	if(mInfoTB)
		mInfoTB->SetText(FText::FromString(info_string));
}
