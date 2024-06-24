// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/Button.h"

#include "Blueprint/UserWidget.h"
#include "ReadyWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UReadyWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UButton* mTutorialButton;
	UButton* mStartButton;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void TutorialButtonHovered();
	UFUNCTION()
	void TutorialButtonUnHovered();
	UFUNCTION()
	void TutorialButtonPressed();
	UFUNCTION()
	void TutorialButtonReleased();
	UFUNCTION()
	void TutorialButtonClick();


	UFUNCTION()
	void StartButtonHovered();
	UFUNCTION()
	void StartButtonUnHovered();
	UFUNCTION()
	void StartButtonPressed();
	UFUNCTION()
	void StartButtonReleased();
	UFUNCTION()
	void StartButtonClick();
};
