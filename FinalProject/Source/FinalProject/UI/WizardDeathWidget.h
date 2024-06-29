// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "WizardDeathWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UWizardDeathWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UTextBlock* DeathText;
	UButton* mRespawnButton;
	UButton* mResetButton;

protected:
	virtual void NativePreConstruct();
	virtual void NativeConstruct();

public:
	void SetDeathWidgetEnable();

	UFUNCTION()
	void RespawnButtonHovered();
	UFUNCTION()
	void RespawnButtonUnHovered();
	UFUNCTION()
	void RespawnButtonPressed();
	UFUNCTION()
	void RespawnButtonReleased();
	UFUNCTION()
	void RespawnButtonClick();


	UFUNCTION()
	void ResetButtonHovered();
	UFUNCTION()
	void ResetButtonUnHovered();
	UFUNCTION()
	void ResetButtonPressed();
	UFUNCTION()
	void ResetButtonReleased();
	UFUNCTION()
	void ResetButtonClick();
};
