// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"

class FINALPROJECT_API CNetSession
{
public:
	CNetSession();
	~CNetSession();

private:
	// 어떤 소켓인지 이름 저장을 위한 변수
	FString mName;
	// FSocket 저장
	FSocket* mSocket = nullptr;
	// 다른 서버에 연결됐는지 판단
	bool mConnect = false;

	uint8 mRecvBuffer[1024] = {};
	uint8 mSendBuffer[1024] = {};

public:
	bool Connect(const FString& IPAddr, int32 Port);
	void Close();
};

