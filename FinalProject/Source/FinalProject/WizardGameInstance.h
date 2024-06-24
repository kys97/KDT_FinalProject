// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "WizardGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FINALPROJECT_API UWizardGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	FString mWizardName;
	EWizardJob mWizardJob;

public:
	void SetWizardName(FString name)
	{
		mWizardName = name;
	}
	UFUNCTION(BlueprintCallable)
	FString GetWizardName()
	{
		return mWizardName;
	}

	void SetWizardJob(EWizardJob job)
	{
		mWizardJob = job;
	}
	EWizardJob GetWizardJob()
	{
		return mWizardJob;
	}
};
