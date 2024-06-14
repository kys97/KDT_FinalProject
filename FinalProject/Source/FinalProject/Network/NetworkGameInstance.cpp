// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkGameInstance.h"
#include "NetworkManager.h"
#include "Thread/ThreadMgr.h"

UNetworkGameInstance::UNetworkGameInstance()
{
}

void UNetworkGameInstance::Init()
{
	Super::Init();

	CNetworkManager::GetInst()->Init();

	// 스레드 관리자 초기화
	CThreadMgr::GetInst()->Init();
}

void UNetworkGameInstance::FinishDestroy()
{
	Super::FinishDestroy();

	CNetworkManager::DestroyInst();

	CThreadMgr::DestroyInst();
}

