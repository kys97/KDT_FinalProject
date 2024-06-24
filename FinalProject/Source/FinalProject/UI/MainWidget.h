// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UEditableTextBox* mInputName;
	UButton* mOKButton;

private:
	int32 mTextByteLength = 0;

protected:
	virtual void NativeConstruct();

public:
	UFUNCTION()
	void InputNameTextChanged(const FText& text);

	UFUNCTION()
	void OkButtonClick();
};
