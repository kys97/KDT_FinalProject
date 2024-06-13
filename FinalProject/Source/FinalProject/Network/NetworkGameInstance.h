// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Engine/GameInstance.h"
#include "NetworkGameInstance.generated.h"

UCLASS()
class FINALPROJECT_API UNetworkGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UNetworkGameInstance();

public:
	virtual void Init();
	// 인스턴스가 제거될 때 동작
	virtual void FinishDestroy();
	
};
