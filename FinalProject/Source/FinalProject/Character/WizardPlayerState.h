// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/PlayerState.h"
#include "WizardPlayerState.generated.h"


// 플레이어 직업 ENUM
UENUM(BlueprintType)
enum class EWizardJob : uint8
{
	None,
	Blue,
	Green,
	Red,
	White,
	Black,
	Count
};


// 직업별 초기 데이터 정보들
USTRUCT(BlueprintType)
struct FWizardData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
	EWizardJob mJob;

	UPROPERTY(EditAnywhere)
	int32 mNormalAttackPoint;
	UPROPERTY(EditAnywhere)
	float mNormalAttackDistance;
	UPROPERTY(EditAnywhere)
	int32 mArmorPoint;

	UPROPERTY(EditAnywhere)
	int32 mHPMax;
	UPROPERTY(EditAnywhere)
	int32 mMPMax;
};


// 플레이어가 실제로 들고 있어야 하는 정보들
UCLASS()
class FINALPROJECT_API AWizardPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AWizardPlayerState();

private:
	UDataTable* mWizardDataTable;

public:
	FString mName;

	EWizardJob mJob;


	int32 mNormalAttackPoint;

	float mNormalAttackDistance;

	int32 mArmorPoint;

	
	int32 mHP;

	int32 mHPMax;

	
	int32 mMP;

	int32 mMPMax;

	
	int32 mLevel;

	int32 mExp;

protected:
	virtual void BeginPlay() override;

};
