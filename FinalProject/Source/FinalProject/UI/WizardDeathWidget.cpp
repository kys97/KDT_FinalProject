// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardDeathWidget.h"
#include "../WizardGameInstance.h"

void UWizardDeathWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UWizardDeathWidget::NativeConstruct()
{
	Super::NativeConstruct();

	DeathText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Death_TB")));
	mRespawnButton = Cast<UButton>(GetWidgetFromName(TEXT("Respawn_Btn")));
	mResetButton = Cast<UButton>(GetWidgetFromName(TEXT("Reset_Btn")));

	FString text = GetGameInstance<UWizardGameInstance>()->GetWizardName() + FString::Printf(TEXT(" Wizard Death!"));
	DeathText->SetText(FText::FromString(text));

	mRespawnButton->OnHovered.AddDynamic(this, &UWizardDeathWidget::RespawnButtonHovered);
	mRespawnButton->OnUnhovered.AddDynamic(this, &UWizardDeathWidget::RespawnButtonUnHovered);
	mRespawnButton->OnPressed.AddDynamic(this, &UWizardDeathWidget::RespawnButtonPressed);
	mRespawnButton->OnReleased.AddDynamic(this, &UWizardDeathWidget::RespawnButtonReleased);
	mRespawnButton->OnClicked.AddDynamic(this, &UWizardDeathWidget::RespawnButtonClick);

	mResetButton->OnHovered.AddDynamic(this, &UWizardDeathWidget::ResetButtonHovered);
	mResetButton->OnUnhovered.AddDynamic(this, &UWizardDeathWidget::ResetButtonUnHovered);
	mResetButton->OnPressed.AddDynamic(this, &UWizardDeathWidget::ResetButtonPressed);
	mResetButton->OnReleased.AddDynamic(this, &UWizardDeathWidget::ResetButtonReleased);
	mResetButton->OnClicked.AddDynamic(this, &UWizardDeathWidget::ResetButtonClick);

	SetVisibility(ESlateVisibility::Hidden);
}

void UWizardDeathWidget::SetDeathWidgetEnable()
{
	SetIsEnabled(true);
	SetVisibility(ESlateVisibility::Visible);
}

void UWizardDeathWidget::RespawnButtonHovered()
{
	mRespawnButton->SetRenderScale(FVector2D(1.2f, 1.2f));
}

void UWizardDeathWidget::RespawnButtonUnHovered()
{
	mRespawnButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UWizardDeathWidget::RespawnButtonPressed()
{
	mRespawnButton->SetRenderScale(FVector2D(0.9f, 0.9f));
}

void UWizardDeathWidget::RespawnButtonReleased()
{
	mRespawnButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UWizardDeathWidget::RespawnButtonClick()
{
	GetGameInstance<UWizardGameInstance>()->RespawnGame();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainGame"));
}

void UWizardDeathWidget::ResetButtonHovered()
{
	mResetButton->SetRenderScale(FVector2D(1.2f, 1.2f));
}

void UWizardDeathWidget::ResetButtonUnHovered()
{
	mResetButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UWizardDeathWidget::ResetButtonPressed()
{
	mResetButton->SetRenderScale(FVector2D(0.9f, 0.9f));
}

void UWizardDeathWidget::ResetButtonReleased()
{
	mResetButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UWizardDeathWidget::ResetButtonClick()
{
	GetGameInstance<UWizardGameInstance>()->ResetGame();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}
