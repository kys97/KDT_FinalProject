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

	int32 mWizardLevel = 1;
	int32 mWizardExp = 0;
	bool mRespawn = false;
	bool mTutorial = false;

	AWizardPlayerState* mWizardPlayerState;
	int32 mHPPotionCount = 0;
	int32 mMPPotionCount = 0;
	int32 mAttackItemCount = 0;
	int32 mArmorItemCount = 0;

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
	void SetItems(int32 hp, int32 mp, int32 attack, int32 armor)
	{
		mHPPotionCount = hp;
		mMPPotionCount = mp;
		mAttackItemCount = attack;
		mArmorItemCount = armor;
	}
	int32 GetHpItemCnt() { return mHPPotionCount; }
	int32 GetMpItemCnt() { return mMPPotionCount; }
	int32 GetAttackItemCnt() { return mAttackItemCount; }
	int32 GetArmorItemCnt() { return mArmorItemCount; }

	UFUNCTION(BlueprintCallable)
	bool IsTutorial() { return mTutorial; }
	UFUNCTION(BlueprintCallable)
	void SetTutorial(bool tutorial) { mTutorial = tutorial; }

	bool IsRespawn() { return mRespawn; }
	void SetRespawn(bool is_respawn) { mRespawn = is_respawn; }
	void RespawnGame()
	{
		mWizardLevel *= 0.7f;
		if (mWizardLevel < 1) mWizardLevel = 1;
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
