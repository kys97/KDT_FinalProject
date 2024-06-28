// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"

#include "Character/WizardPlayerState.h"

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

	int32 mWizardLevel = 0;
	int32 mWizardExp = 0;
	bool mRespawn = false;

	AWizardPlayerState* mWizardPlayerState;

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

	void SetLevel(int32 level) { mWizardLevel = level; }
	int32 GetLevel() { return mWizardLevel; }
	UFUNCTION(BlueprintCallable)
	FString GetLevelString()
	{
		return FString::Printf(TEXT("Lv.%d "), mWizardLevel);
	}

	AWizardPlayerState* GetState() { return mWizardPlayerState; }
	void SetState(AWizardPlayerState* state) { mWizardPlayerState = state; }

	
	bool IsRespawn() { return mRespawn; }
	void RespawnGame()
	{
		mWizardLevel *= 0.7f;
		mWizardExp = 0;
		mRespawn = true;
	}
	void ResetGame()
	{
		mWizardName = nullptr;
		mWizardLevel = 0;
		mWizardExp = 0;
		mRespawn = false;
	}
};
