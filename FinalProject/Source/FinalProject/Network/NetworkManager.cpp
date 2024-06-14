// Fill out your copyright notice in the Description page of Project Settings.

#include "NetworkManager.h"
#include "NetSession.h"

CNetworkManager* CNetworkManager::mInst = nullptr;

CNetworkManager::CNetworkManager()
{
}

CNetworkManager::~CNetworkManager()
{
	for (auto& Session : mSessionMap)
	{
		Session.Value->Close();

		delete Session.Value;
	}
}

bool CNetworkManager::Init()
{
	return true;
}

bool CNetworkManager::CheckSession(const FString& Name)
{
	return mSessionMap.Contains(Name);
}

bool CNetworkManager::Connet(const FString& Name, const FString& IPAddr, int32 Port)
{
	CNetSession* Session = nullptr;

	// 해당 이름의 세션이 없을 경우 생성해준다.
	if (!CheckSession(Name))
	{
		Session = new CNetSession;

		Session->SetName(Name);
		// 맵에 세션 추가
		mSessionMap.Emplace(Name, Session);
	}

	// 해당 이름의 세션이 있을 경우 찾아준다.
	else
		Session = FindSession(Name);

	if (Session->IsConnect())
		return false;

	return Session->Connect(IPAddr, Port);
}

bool CNetworkManager::Close(const FString& Name)
{
	if (!mSessionMap.Contains(Name))
		return false;

	CNetSession* Session = FindSession(Name);

	if (!Session->IsConnect())
		return false;

	Session->Close();

	return true;
}

CNetSession* CNetworkManager::FindSession(const FString& Name)
{
	if (!mSessionMap.Contains(Name))
		return nullptr;

	return mSessionMap.FindRef(Name);
}

bool CNetworkManager::RemoveSession(const FString& Name)
{
	return false;
}

bool CNetworkManager::Send(const FString& Name, int32 PacketHeader, int32 Length, uint8* Packet)
{
	return false;
}
