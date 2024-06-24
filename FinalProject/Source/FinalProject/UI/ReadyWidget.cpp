// Fill out your copyright notice in the Description page of Project Settings.


#include "ReadyWidget.h"
#include "Components/CanvasPanelSlot.h"

void UReadyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mTutorialButton = Cast<UButton>(GetWidgetFromName(TEXT("Tutorial_Btn")));
	mStartButton = Cast<UButton>(GetWidgetFromName(TEXT("Start_Btn")));

	mTutorialButton->OnHovered.AddDynamic(this, &UReadyWidget::TutorialButtonHovered);
	mTutorialButton->OnUnhovered.AddDynamic(this, &UReadyWidget::TutorialButtonUnHovered);
	mTutorialButton->OnPressed.AddDynamic(this, &UReadyWidget::TutorialButtonPressed);
	mTutorialButton->OnReleased.AddDynamic(this, &UReadyWidget::TutorialButtonReleased);
	mTutorialButton->OnClicked.AddDynamic(this, &UReadyWidget::TutorialButtonClick);

	mStartButton->OnHovered.AddDynamic(this, &UReadyWidget::StartButtonHovered);
	mStartButton->OnUnhovered.AddDynamic(this, &UReadyWidget::StartButtonUnHovered);
	mStartButton->OnPressed.AddDynamic(this, &UReadyWidget::StartButtonPressed);
	mStartButton->OnReleased.AddDynamic(this, &UReadyWidget::StartButtonReleased);
	mStartButton->OnClicked.AddDynamic(this, &UReadyWidget::StartButtonClick);
}

void UReadyWidget::TutorialButtonHovered()
{
	mTutorialButton->SetRenderScale(FVector2D(1.2f, 1.2f));
}

void UReadyWidget::TutorialButtonUnHovered()
{
	mTutorialButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UReadyWidget::TutorialButtonPressed()
{
	mTutorialButton->SetRenderScale(FVector2D(0.9f, 0.9f));
}

void UReadyWidget::TutorialButtonReleased()
{
	mTutorialButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UReadyWidget::TutorialButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Tutorial"));
}

void UReadyWidget::StartButtonHovered()
{
	mStartButton->SetRenderScale(FVector2D(1.2f, 1.2f));
}

void UReadyWidget::StartButtonUnHovered()
{
	mStartButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UReadyWidget::StartButtonPressed()
{
	mStartButton->SetRenderScale(FVector2D(0.9f, 0.9f));
}

void UReadyWidget::StartButtonReleased()
{
	mStartButton->SetRenderScale(FVector2D(1.0f, 1.0f));
}

void UReadyWidget::StartButtonClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("InGame"));
}
