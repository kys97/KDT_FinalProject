// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "WizardInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UWizardInfoWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UTextBlock* mInfoTB;

protected:
	virtual void NativeConstruct();

public:
	void SetWizardInfoText(FString info_string);
};
