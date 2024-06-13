// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"
#include "NetworkManager.h"

UNetworkGameInstance::UNetworkGameInstance()
{
}

void UNetworkGameInstance::Init()
{
	Super::Init();

	CNetworkManager::GetInst()->Init();
}

void UNetworkGameInstance::FinishDestroy()
{
	Super::FinishDestroy();

	CNetworkManager::DestroyInst();
}

