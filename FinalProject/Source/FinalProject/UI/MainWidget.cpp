// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "../WizardGameInstance.h"


void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mInputName = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Name_ET")));
	mOKButton = Cast<UButton>(GetWidgetFromName(TEXT("OK_Btn")));
	
	mInputName->OnTextChanged.AddDynamic(this, &UMainWidget::InputNameTextChanged);
	mOKButton->OnClicked.AddDynamic(this, &UMainWidget::OkButtonClick);
}

void UMainWidget::InputNameTextChanged(const FText& text)
{
	FString InputText = text.ToString();
	int len = InputText.Len();
	mTextByteLength = 0;

	for (int i = 0; i < len; i++)
	{
		if ((InputText[i] >= 0xAC00 && InputText[i] <= 0xD7A3) // Korean - Complete
			|| (InputText[i] >= 0x3131 && InputText[i] <= 0x3163)) // Korean - Not Complete
		{
			mTextByteLength += 2;
		}
		else if (InputText[i] >= 'A' && InputText[i] <= 'Z' // Upper English
			|| InputText[i] >= 'a' && InputText[i] <= 'z' // Lower English
			|| InputText[i] >= 0x0030 && InputText[i] <= 0x0039) // Number
		{
			mTextByteLength++;
		}
		else // Other Language
		{
			InputText.RemoveAt(InputText.Len() - 1);
			mInputName->SetText(FText::FromString(InputText));
		}
	}

	if (mTextByteLength > 10)
	{
		InputText.RemoveAt(InputText.Len() - 1);
		mInputName->SetText(FText::FromString(InputText));
	}
}

void UMainWidget::OkButtonClick()
{
	if (mInputName->GetText().IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("텍스트 empty")));
		return;
	}

	GetGameInstance<UWizardGameInstance>()->SetWizardName(mInputName->GetText().ToString());

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Ready"));
}
