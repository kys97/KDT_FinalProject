// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

/**
 * 
 */
class FINALPROJECT_API CNetworkManager
{
private:
	CNetworkManager();
	~CNetworkManager();

private:
	TMap<FString, class CNetSession*> mSessionMap;

public:
	bool Init();
	// 세션 있는지 체크
	bool CheckSession(const FString& Name);
	// 세션 연결
	bool Connet(const FString& Name, const FString& IPAddr, int32 Port);
	// 세션 닫는 함수
	bool Close(const FString& Name);
	// 세션 찾는 함수
	class CNetSession* FindSession(const FString& Name);
	// 세션 제거
	bool RemoveSession(const FString& Name);
	// 특정 세션을 찾아 데이터를 보내주는 함수
	bool Send(const FString& Name, int32 PacketHeader, int32 Length, uint8* Packet);

private:
	static CNetworkManager* mInst;

public:
	static CNetworkManager* GetInst()
	{
		if (!mInst)
			mInst = new CNetworkManager;

		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};
