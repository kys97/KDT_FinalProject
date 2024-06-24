// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

#include "Input/InputDataConfig.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "GameFramework/PlayerController.h"
#include "WizardPlayerController.generated.h"


UCLASS()
class FINALPROJECT_API AWizardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AWizardPlayerController();

protected:
	TSubclassOf<UUserWidget> mGameWidgetClass = nullptr;
	class UGameWidget* mGameWidget = nullptr;
	
public:
	UGameWidget* GetGameWidget() { return mGameWidget; }

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void EndMove(const FInputActionValue& InputActionValue);
};
